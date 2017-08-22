//import FPWCSApi2

let IS_IPAD = (UI_USER_INTERFACE_IDIOM() == .pad)
class WCSViewUtil: NSObject {
    class func createTextField(_ delegate: UITextFieldDelegate) -> UITextField {
        let textField = UITextField()
        textField.borderStyle = .roundedRect
        textField.contentVerticalAlignment = .center
        textField.font = UIFont.boldSystemFont(ofSize: 12)
        textField.translatesAutoresizingMaskIntoConstraints = false
        textField.returnKeyType = .done
        textField.delegate = delegate
        return textField
    }

    class func createTextView() -> UITextView {
        let textView = UITextView()
        textView.font = UIFont.boldSystemFont(ofSize: 12)
        textView.translatesAutoresizingMaskIntoConstraints = false
        textView.textAlignment = .center
        textView.isEditable = false
        textView.text = "NO STATUS"
        return textView
    }

    class func createLabelView() -> UILabel {
        let textView = UILabel()
        textView.font = UIFont.boldSystemFont(ofSize: 12)
        textView.translatesAutoresizingMaskIntoConstraints = false
        textView.textAlignment = .center
        textView.text = "NO STATUS"
        return textView
    }

    class func createInfoLabel(_ infoText: String) -> UILabel {
        let label = UILabel()
        label.font = UIFont.boldSystemFont(ofSize: 12)
        label.translatesAutoresizingMaskIntoConstraints = false
        label.textAlignment = .left
        label.text = infoText
        return label
    }

    class func createSwitch() -> UISwitch {
        let uiSwitch = UISwitch()
        uiSwitch.translatesAutoresizingMaskIntoConstraints = false
        return uiSwitch
    }

    class func createPicker(_ delegate: Any) -> UIPickerView {
        let picker = UIPickerView()
        picker.dataSource = delegate as! UIPickerViewDataSource
        picker.delegate = delegate as! UIPickerViewDelegate
        picker.showsSelectionIndicator = true
        return picker
    }

    class func createButton(_ title: String) -> UIButton {
        let button = UIButton(type: .custom)
        button.backgroundColor = UIColor.lightGray
        button.layer.borderWidth = 2.0
        button.layer.cornerRadius = 6.0
        button.setTitle(title, for: .normal)
        button.translatesAutoresizingMaskIntoConstraints = false
        return button
    }

    class func createBorder(_ thickness: NSNumber) -> UIView {
        let border = UIView()
        border.translatesAutoresizingMaskIntoConstraints = false
        border.backgroundColor = UIColor.black
        border.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "V:[border(thickness)]", options: [], metrics: ["thickness": thickness], views: ["border": border]))
        return border
    }
}

class WCSStack: NSObject {
    private(set) var count: Int = 0

    var data = [Any]()

    override init() {
        super.init()

        data = [Any]()
        count = 0

    }

    func push(_ anObject: Any) {
        data.append(anObject)
        count += 1
    }

    func pop() -> Any {
        var obj: Any? = nil
        if data.count > 0 {
            obj = data.last
            data.removeLast()
            count = data.count
        }
        return obj!
    }

    func clear() {
        data.removeAll()
        count = 0
    }

    var lastObject: Any? {
        var obj: Any? = nil
        if data.count > 0 {
            obj = data.last
        }
        return obj!
    }
}
