import AVFoundation
import UIKit

class ViewController: UIViewController {
    var scrollView: UIScrollView?
    var contentView: UIView?
    var connectUrl: UITextField?
    var playStreamLabel: UILabel?
    var remoteStreamName: UITextField?
    var status: UILabel?
    var startButton: UIButton?
    var videoContainer: UIView?
    var remoteDisplay: RTCEAGLVideoView?
    var remoteDisplayConstraints = [NSLayoutConstraint]()

    //user interface handlers
    @IBAction func start(_ button: UIButton) {
        changeViewState(button, enabled: false)
        if (button.titleLabel?.text == "STOP") {
            if FPWCSApi2.getSessions().count > 0 {
                if let session: FPWCSApi2Session = FPWCSApi2.getSessions()?[0] as? FPWCSApi2Session {
                    print("Disconnect session with server \(session.getServerUrl()!)")
                    session.disconnect()
                }
            }
            else {
                print("Nothing to disconnect")
                onDisconnected()
            }
        }
        else {
            changeViewState(connectUrl!, enabled: false)
            connect()
        }
    }
}

extension ViewController {
    override func viewDidLoad() {
        super.viewDidLoad()
        setupViews()
        setupLayout()
        onDisconnected()
        print("Did load views")
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
}

extension ViewController {
    func connect() -> FPWCSApi2Session? {
        let options:FPWCSApi2SessionOptions = FPWCSApi2SessionOptions()
        options.urlServer = connectUrl!.text
        options.appKey = "defaultApp"
        var error: Error?
        do {
            let session:FPWCSApi2Session = try FPWCSApi2.createSession(options)

            session.on(.fpwcsSessionStatusEstablished, callback: {(_ rSession: FPWCSApi2Session?) -> Void in
                self.changeConnectionStatus(rSession?.getStatus())
                self.onConnected(rSession)
            })
            session.on(.fpwcsSessionStatusDisconnected, callback: {(_ rSession: FPWCSApi2Session?) -> Void in
                self.changeConnectionStatus(rSession?.getStatus())
                self.onDisconnected()
            })
            session.on(.fpwcsSessionStatusFailed, callback: {(_ rSession: FPWCSApi2Session?) -> Void in
                self.changeConnectionStatus(rSession?.getStatus())
                self.onDisconnected()
            })
            session.connect()
            return session
        }
        catch let error {
            let alert = UIAlertController(title: "Failed to connect", message: error.localizedDescription, preferredStyle: .alert)
            let okButton = UIAlertAction(title: "Ok", style: .default, handler: {(_ action: UIAlertAction) -> Void in
                self.onDisconnected()
            })
            alert.addAction(okButton)
            present(alert, animated: true) { _ in }
            return nil
        }
    }

    func playStream() -> FPWCSApi2Stream? {
        let session: FPWCSApi2Session = FPWCSApi2.getSessions()?[0] as! FPWCSApi2Session
        let options = FPWCSApi2StreamOptions()
        options.name = remoteStreamName!.text
        options.display = remoteDisplay
        var error: Error?
        let stream: FPWCSApi2Stream? = try? session.createStream(options)
        if stream == nil {
            let alert = UIAlertController(title: "Failed to play", message: error?.localizedDescription, preferredStyle: .alert)
            let okButton = UIAlertAction(title: "Ok", style: .default, handler: {(_ action: UIAlertAction) -> Void in
                self.onStopped()
            })
            alert.addAction(okButton)
            present(alert, animated: true) { _ in }
            return nil
        }
        stream!.on(.fpwcsStreamStatusPlaying, callback: {(_ rStream: FPWCSApi2Stream?) -> Void in
            self.changeStreamStatus(rStream)
            self.onPlaying(rStream)
        })
        stream!.on(.fpwcsStreamStatusNotEnoughtBandwidth, callback: {(_ rStream: FPWCSApi2Stream?) -> Void in
            print("Not enough bandwidth stream \(rStream!.getName()), consider using lower video resolution or bitrate. Bandwidth \(stream!.getNetworkBandwidth() / 1000) bitrate \(stream!.getRemoteBitrate() / 1000)")
            self.changeStreamStatus(rStream)
        })
        stream!.on(.fpwcsStreamStatusStopped, callback: {(_ rStream: FPWCSApi2Stream?) -> Void in
            self.changeStreamStatus(rStream)
            self.onDisconnected()
        })
        stream!.on(.fpwcsStreamStatusFailed, callback: {(_ rStream: FPWCSApi2Stream?) -> Void in
            self.changeStreamStatus(rStream)
            self.onDisconnected()
        })
        do {
            let playing = try stream!.play()
        } catch let error {
            let alert = UIAlertController(title: "Failed to play", message: error.localizedDescription, preferredStyle: .alert)
            let okButton = UIAlertAction(title: "Ok", style: .default, handler: {(_ action: UIAlertAction) -> Void in
            })
            alert.addAction(okButton)
            present(alert, animated: true) { _ in }
        }

        return stream
    }
}

extension ViewController {
    //session and stream status handlers
    func onConnected(_ session: FPWCSApi2Session?) {
        changeViewState(remoteStreamName!, enabled: false)
        playStream()
    }

    func onDisconnected() {
        changeViewState(connectUrl!, enabled: true)
        onStopped()
    }

    func onPlaying(_ stream: FPWCSApi2Stream?) {
        startButton!.setTitle("STOP", for: .normal)
        changeViewState(startButton!, enabled: true)
    }

    func onStopped() {
        startButton!.setTitle("START", for: .normal)
        changeViewState(startButton!, enabled: true)
        changeViewState(remoteStreamName!, enabled: true)
//        remoteDisplay!.renderFrame(nil)
    }
}

extension ViewController {
    //status handlers
    func changeConnectionStatus(_ status: kFPWCSSessionStatus?) {
        if let status = status {
            self.status!.text = FPWCSApi2Model.sessionStatus(toString: status)
            switch status {
            case .fpwcsSessionStatusFailed:
                self.status!.textColor = UIColor.red
            case .fpwcsSessionStatusEstablished:
                self.status!.textColor = UIColor.green
            default:
                self.status!.textColor = UIColor.darkText
            }
        }
    }

    func changeStreamStatus(_ stream: FPWCSApi2Stream?) {
        if let stream = stream {
            status!.text = FPWCSApi2Model.streamStatus(toString: stream.getStatus())
            switch stream.getStatus() {
            case .fpwcsStreamStatusFailed:
                status!.textColor = UIColor.red
            case .fpwcsStreamStatusPlaying, .fpwcsStreamStatusPublishing:
                status!.textColor = UIColor.green
            default:
                status!.textColor = UIColor.darkText
            }
        }
    }
}

extension ViewController {
    //button state helper
    func changeViewState(_ button: UIView, enabled: Bool) {
        button.isUserInteractionEnabled = enabled
        if enabled {
            button.alpha = 1.0
        }
        else {
            button.alpha = 0.5
        }
    }
}

extension ViewController {
    //user interface views and layout

    func setupViews() {
        //views main->scroll->content-videoContainer-display
        scrollView = UIScrollView()
        scrollView!.translatesAutoresizingMaskIntoConstraints = false
        scrollView!.isScrollEnabled = true
        contentView = UIView()
        contentView!.translatesAutoresizingMaskIntoConstraints = false
        videoContainer = UIView()
        videoContainer!.translatesAutoresizingMaskIntoConstraints = false
        remoteDisplay = RTCEAGLVideoView()
        remoteDisplay!.delegate = self
        remoteDisplay!.translatesAutoresizingMaskIntoConstraints = false
        connectUrl = WCSViewUtil.createTextField(self)
        playStreamLabel = WCSViewUtil.createInfoLabel("Play Stream")
        remoteStreamName = WCSViewUtil.createTextField(self)
        status = WCSViewUtil.createLabelView()
        startButton = WCSViewUtil.createButton("PLAY")
        startButton!.addTarget(self, action: #selector(self.start), for: .touchUpInside)
        videoContainer!.addSubview(remoteDisplay!)
        contentView!.addSubview(connectUrl!)
        contentView!.addSubview(playStreamLabel!)
        contentView!.addSubview(remoteStreamName!)
        contentView!.addSubview(status!)
        contentView!.addSubview(startButton!)
        contentView!.addSubview(videoContainer!)
        scrollView!.addSubview(contentView!)
        view.addSubview(scrollView!)
        //set default values
        connectUrl!.text = "wss://wcs5-eu.flashphoner.com:8443/"
        remoteStreamName!.text = "streamName"
    }

    func setupLayout() {
        let views: [AnyHashable: Any] = [
                "connectUrl": connectUrl,
                "playStreamLabel": playStreamLabel,
                "remoteStreamName": remoteStreamName,
                "status": status,
                "startButton": startButton,
                "remoteDisplay": remoteDisplay,
                "videoContainer": videoContainer,
                "contentView": contentView,
                "scrollView": scrollView
        ]

        let metrics: [AnyHashable: Any] = [
                "buttonHeight": 30,
                "statusHeight": 30,
                "labelHeight": 20,
                "inputFieldHeight": 30,
                "vSpacing": 15,
                "hSpacing": 30
        ]

        //constraint helpers
        let setConstraintWithItem: ((_: UIView, _: UIView, _: UIView, _: NSLayoutAttribute, _: NSLayoutRelation, _: NSLayoutAttribute, _: CGFloat, _: CGFloat) -> NSLayoutConstraint)?? = {
            (_ dst: UIView, _ with: UIView, _ to: UIView, _ attr1: NSLayoutAttribute, _ relation: NSLayoutRelation, _ attr2: NSLayoutAttribute, _ multiplier: CGFloat, _ constant: CGFloat) -> NSLayoutConstraint in
            let constraint = NSLayoutConstraint(item: with, attribute: attr1, relatedBy: relation, toItem: to, attribute: attr2, multiplier: multiplier, constant: constant)
            dst.addConstraint(constraint)
            return constraint
        }

        let setConstraint: ((_: UIView, _: String, _: NSLayoutFormatOptions) -> Void)? = {
            (_ view: UIView, _ constraint: String, _ options: NSLayoutFormatOptions) -> Void in
            view.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: constraint as? String ?? "", options: options, metrics: metrics as? [String: Any] ?? [String: Any](), views: views as? [String: Any] ?? [String: Any]()))
        }

        remoteDisplayConstraints = [NSLayoutConstraint]()
        //set height size
        setConstraint!(connectUrl!, "V:[connectUrl(inputFieldHeight)]", NSLayoutFormatOptions(rawValue: 0))
        setConstraint!(playStreamLabel!, "V:[playStreamLabel(labelHeight)]", NSLayoutFormatOptions(rawValue: 0))
        setConstraint!(remoteStreamName!, "V:[remoteStreamName(inputFieldHeight)]", NSLayoutFormatOptions(rawValue: 0))
        setConstraint!(status!, "V:[status(statusHeight)]", NSLayoutFormatOptions(rawValue: 0))
        setConstraint!(startButton!, "V:[startButton(buttonHeight)]", NSLayoutFormatOptions(rawValue: 0))
        //set width related to super view
        setConstraint!(contentView!, "H:|-hSpacing-[connectUrl]-hSpacing-|", NSLayoutFormatOptions(rawValue: 0))
        setConstraint!(contentView!, "H:|-hSpacing-[playStreamLabel]-hSpacing-|", NSLayoutFormatOptions(rawValue: 0))
        setConstraint!(contentView!, "H:|-hSpacing-[remoteStreamName]-hSpacing-|", NSLayoutFormatOptions(rawValue: 00))
        setConstraint!(contentView!, "H:|-hSpacing-[status]-hSpacing-|", NSLayoutFormatOptions(rawValue: 0))
        setConstraint!(contentView!, "H:|-hSpacing-[startButton]-hSpacing-|", NSLayoutFormatOptions(rawValue: 0))
        setConstraint!(contentView!, "H:|-hSpacing-[videoContainer]-hSpacing-|", NSLayoutFormatOptions(rawValue: 0))
        //remote display max width and height
        setConstraintWithItem!!(videoContainer!, remoteDisplay!, videoContainer!, .width, .lessThanOrEqual, .width, 1.0, 0)
        //remote display aspect ratio
        let remoteARConstraint: NSLayoutConstraint = setConstraintWithItem!!(remoteDisplay!, remoteDisplay!, remoteDisplay!, .width, .equal, .height, 640.0 / 480.0, 0)
        remoteDisplayConstraints.append(remoteARConstraint)
        //position video views inside video container
        setConstraint!(videoContainer!, "H:|[remoteDisplay]|", .alignAllTop)
        setConstraint!(videoContainer!, "V:|[remoteDisplay]|", NSLayoutFormatOptions(rawValue: 0))
        setConstraint!(contentView!, "V:|-50-[connectUrl]-vSpacing-[playStreamLabel]-vSpacing-[remoteStreamName]-vSpacing-[status]-vSpacing-[startButton]-vSpacing-[videoContainer]-vSpacing-|", NSLayoutFormatOptions(rawValue: 0))
        //content view width
        setConstraintWithItem!!(view!, contentView!, view!, .width, .equal, .width, 1.0, 0)
        //position content and scroll views
        setConstraint!(view!, "V:|[contentView]|", NSLayoutFormatOptions(rawValue: 0))
        setConstraint!(view!, "H:|[contentView]|", NSLayoutFormatOptions(rawValue: 0))
        setConstraint!(view!, "V:|[scrollView]|", NSLayoutFormatOptions(rawValue: 0))
        setConstraint!(view!, "H:|[scrollView]|", NSLayoutFormatOptions(rawValue: 0))
    }
}

extension ViewController : RTCEAGLVideoViewDelegate {
    func videoView(_ videoView: RTCEAGLVideoView, didChangeVideoSize size: CGSize) {
        print("Size of remote video \(size.width)\(size.height)")
        remoteDisplay!.removeConstraints(remoteDisplayConstraints)
        remoteDisplayConstraints.removeAll()
        let constraint = NSLayoutConstraint(item: remoteDisplay, attribute: .width, relatedBy: .equal, toItem: remoteDisplay, attribute: .height, multiplier: size.width / size.height, constant: 0.0)
        remoteDisplayConstraints.append(constraint)
        remoteDisplay!.addConstraints(remoteDisplayConstraints)
    }
}

extension ViewController : UITextFieldDelegate {
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true
    }
}