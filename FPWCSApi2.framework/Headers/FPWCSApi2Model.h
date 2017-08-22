//
//  FPWCSApi2Model.h
//  FPWCSApi
//
//  Created by user on 17/10/2016.
//  Copyright © 2016 user. All rights reserved.
//

#import "RTCEAGLVideoView.h"
#import "RTCConfiguration.h"
#import <JSONModel/JSONModel.h>

/**
 `kFPWCSConnectionStatus` is an enum reflecting status of connection to WCS server.
 */
typedef NS_ENUM(NSInteger, kFPWCSSessionStatus) {
    kFPWCSSessionStatusNew,
    kFPWCSSessionStatusPending,
    kFPWCSSessionStatusEstablished,
    kFPWCSSessionStatusDisconnected,
    kFPWCSSessionStatusFailed,
    kFPWCSSessionStatusRegistered,
    kFPWCSSessionStatusUnregistered
};

/**
 `kFPWCSConnectionStatus` is an enum reflecting status of connection to WCS server.
 */
typedef NS_ENUM(NSInteger, kFPWCSSessionEvent) {
    kFPWCSSessionEventData
};

/**
 `kFPWCSStreamStatus` is an enum reflecting stream status.
 */
typedef NS_ENUM(NSInteger, kFPWCSStreamStatus) {
    kFPWCSStreamStatusNew,
    kFPWCSStreamStatusPending,
    kFPWCSStreamStatusPublishing,
    kFPWCSStreamStatusPlaying,
    kFPWCSStreamStatusPaused,
    kFPWCSStreamStatusUnpublished,
    kFPWCSStreamStatusStopped,
    kFPWCSStreamStatusFailed,
    kFPWCSStreamStatusResize,
    kFPWCSStreamStatusSnaphotComplete,
    kFPWCSStreamStatusNotEnoughtBandwidth
};

/**
 `kFPWCSStreamStatus` is an enum reflecting stream status.
 */
typedef NS_ENUM(NSInteger, kFPWCSCallStatus) {
    kFPWCSCallStatusNew,
    kFPWCSCallStatusTrying,
    kFPWCSCallStatusRing,
    kFPWCSCallStatusBusy,
    kFPWCSCallStatusHold,
    kFPWCSCallStatusEstablished,
    kFPWCSCallStatusFailed,
    kFPWCSCallStatusFinish
};

/**
 Static helpers
 **/
@interface FPWCSApi2Model : NSObject

/**
 Convert session status to string
 
 @param status `kFPWCSSessionStatus` session status
 
 @return `NSString` status string representation
 **/
+ (NSString *)sessionStatusToString:(kFPWCSSessionStatus)status;

/**
 Convert stream status to string
 
 @param status `kFPWCSStreamStatus` stream status
 
 @return `NSString` status string representation
 **/
+ (NSString *)streamStatusToString:(kFPWCSStreamStatus)status;

+ (NSString *)callStatusToString:(kFPWCSCallStatus)status;

+ (kFPWCSCallStatus)callStatusFromString:(NSString*)statusString;

/**
 Convert string to stream status
 
 @param statusString `NSString` stream status
 
 @return `kFPWCSStreamStatus` status enum representation
 **/
+ (kFPWCSStreamStatus)streamStatusFromString:(NSString*)statusString;

@end


/**
 Video contraints
 **/
@interface FPWCSApi2AudioConstraints : NSObject
@property BOOL useFEC;
@property BOOL useStereo;
@property NSInteger bitrate;
@end

/**
 Video contraints
 **/
@interface FPWCSApi2VideoConstraints : NSObject

@property NSString *deviceID;

@property NSInteger minWidth;

@property NSInteger minHeight;

@property NSInteger maxWidth;

@property NSInteger maxHeight;

@property NSInteger minFrameRate;

@property NSInteger maxFrameRate;

@property NSInteger bitrate;

@property NSInteger quality;

@end


/**
 Media constraints
 **/
@interface FPWCSApi2MediaConstraints : NSObject

@property FPWCSApi2AudioConstraints *audio;

@property FPWCSApi2VideoConstraints *video;

- (instancetype)initWithAudio:(BOOL)audio video:(BOOL)video;

- (instancetype)initWithAudio:(BOOL)audio videoWidth:(NSInteger)width videoHeight:(NSInteger)height;

- (instancetype)initWithAudio:(BOOL)audio videoWidth:(NSInteger)width videoHeight:(NSInteger)height videoFps:(NSInteger)fps;

@end

/**
 Session options
 **/
@interface FPWCSApi2SessionOptions : NSObject

@property NSString *urlServer;

@property NSString *appKey;

@property RTCConfiguration *mediaConfig;

@property BOOL sipRegisterRequired;

@property NSString *sipLogin;

@property NSString *sipAuthenticationName;

@property NSString *sipPassword;

@property NSString *sipVisibleName;

@property NSString *sipDomain;

@property NSString *sipOutboundProxy;

@property NSNumber *sipPort;

@property NSMutableDictionary *custom;

@property NSObject *sipOptions;

@end

/**
 Stream options
 **/
@interface FPWCSApi2StreamOptions : NSObject

@property NSString *name;

@property FPWCSApi2MediaConstraints *constraints;

@property NSString *rtmpUrl;

@property BOOL record;

@property RTCEAGLVideoView *display;

@property NSMutableDictionary *custom;

@end

/**
 Call options
 **/
@interface FPWCSApi2CallOptions : NSObject

@property NSString *callee;

@property FPWCSApi2MediaConstraints *localConstraints;

@property FPWCSApi2MediaConstraints *remoteConstraints;

@property RTCEAGLVideoView *localDisplay;

@property RTCEAGLVideoView *remoteDisplay;

@property NSMutableDictionary *custom;

@end

/**
 Media device info
 **/
@interface FPWCSApi2MediaDevice : NSObject

/**
 Can be one of AVMediaTypeVideo, AVMediaTypeAudio
 **/
@property NSString *type;

/**
 Device unique id
 **/
@property NSString *deviceID;

/**
 Device localized name
 **/
@property NSString *label;

@end

/**
 Media devices
 **/
@interface FPWCSApi2MediaDeviceList : NSObject

/**
 Array containing `FPWCSApi2MediaDevice` devices with type audio
 **/
@property NSMutableArray *audio;

/**
 Array containing `FPWCSApi2MediaDevice` devices with type video
 **/
@property NSMutableArray *video;

@end


@interface FPWCSApi2Data : JSONModel

@property NSString *operationId;
@property NSDictionary<Optional> *payload;
@property NSString<Optional> *status;
@property NSString<Optional> *info;

@end



