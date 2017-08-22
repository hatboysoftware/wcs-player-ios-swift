//
//  FPWCSApi2.h
//  FPWCSApi
//
//  Created by user on 17/10/2016.
//  Copyright © 2016 user. All rights reserved.
//

#import "FPWCSApi2Session.h"
#import "FPWCSApi2Model.h"
#import "FPWCSApi2RoomManager.h"
#import "RTCEAGLVideoView.h"

@class FPWCSApi2;

/**
 @remark All work is done in separate dispatch queue that interacts with WebSockets and WebRTC.
 */
@interface FPWCSApi2 : NSObject

/**
 Create new session.
 
 @param options `FPWCSApi2SessionOptions` object with session configuration
 
 @param error `NSError` object to fill with info if error occurs
 
 @return `FPWCSApi2Session` session
 */
+ (FPWCSApi2Session *)createSession:(FPWCSApi2SessionOptions *)options
                              error:(NSError **)error;

+ (FPWCSApi2RoomManager *)createRoomManager:(FPWCSApi2RoomManagerOptions *)options
                                      error:(NSError **)error;

/**
 Get access to local media.
 
 @param constraints `FPWCSAPI2MediaConstraints` media constraints
 
 @param display `RTCEAGLVideoView` View local media should be displayed in
 
 @param error `NSError` object to fill with info if error occurs
 
 @return `BOOL` false if error occured otherwise true
 **/
+ (BOOL)getMediaAccess:(FPWCSApi2MediaConstraints *)constraints
                                display:(RTCEAGLVideoView *)display
                                error:(NSError **)error;

/**
 Get local device list
 
 @return `FPWCSApi2MediaDeviceList` device list
 **/
+ (FPWCSApi2MediaDeviceList *)getMediaDevices;

/**
 Get supported video resolutions
 
 @return `NSArray` array with supported resolutions
 **/
+ (NSArray *)getSupportedVideoResolutions;

/**
 Get session by id.
 
 @param sessionID `NSString` session id
 
 @return `FPWCSApi2Session` session
 **/
+ (FPWCSApi2Session *)getSession:(NSString *)sessionID;

/**
 Get active sessions.
 
 @return `NSArray` sessions
 **/
+ (NSArray *)getSessions;

/**
 Release local media.
 
 @return `BOOL` true if media released
 **/
+ (BOOL)releaseLocalMedia:(RTCEAGLVideoView *)display;

@end

