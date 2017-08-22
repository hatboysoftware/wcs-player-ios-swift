//
//  FPWCSApi2Session.h
//  FPWCSApi
//
//  Created by user on 17/10/2016.
//  Copyright © 2016 user. All rights reserved.
//

#import "FPWCSApi2Stream.h"
#import "FPWCSApi2Call.h"
#import "RTCEAGLVideoView.h"
#import "FPWCSApi2Model.h"

@class FPWCSApi2Session;

/**
 Session callback block.
 **/
typedef void (^SessionCallback)(FPWCSApi2Session *);
typedef void (^SessionAppDataCallback)(FPWCSApi2Session *, FPWCSApi2Data *);

@interface FPWCSApi2DataHandler : NSObject
@property SessionAppDataCallback onAccepted;
@property SessionAppDataCallback onRejected;
@end

/**
 Represents connection to REST App. Can create and store Streams.
 **/
@interface FPWCSApi2Session : NSObject

/**
 Create stream.
 
 @param options `FPWCSApi2StreamOptions` stream configuration options
 
 @param error `NSError` object to fill with info if error occurs
 
 @return `FPWCSApi2Stream` newly created stream
 **/
- (FPWCSApi2Stream *)createStream:(FPWCSApi2StreamOptions *)options error:(NSError **)error;

- (FPWCSApi2Call *)createCall:(FPWCSApi2CallOptions *)options error:(NSError **)error;

/**
 Connect to server.
 Note that connect can be called only once.
 **/
- (void)connect;

/**
 Disconnect from server
 **/
- (void)disconnect;

/**
 Get server address.
 
 @return `NSString` server address
 **/
- (NSString *)getServerUrl;

/**
 Get stream by id.
 
 @param streamID `NSString` stream identificator
 
 @return `FPWCSApi2Stream` stream
 **/
- (FPWCSApi2Stream *)getStream:(NSString *)streamID;

/**
 Get streams.
 
 @return `NSArray` streams
 **/
- (NSArray *)getStreams;

/**
 Get session id
 
 @return `NSStrien session id`
 **/
- (NSString *)getSessionID;

/**
 Add session event callback.
 
 @param event `kFPWCSSessionStatus` event type
 
 @param callback `SessionCallback` callback block
 
 @return `FPWCSApi2Session` session
 **/
- (FPWCSApi2Session *)on:(kFPWCSSessionStatus)event
callback:(SessionCallback)callback;

/**
 Add session event callback.
 
 @param event `kFPWCSSessionStatus` event type
 
 @param callback `SessionCallback` callback block
 
 @return `FPWCSApi2Session` session
 **/
- (FPWCSApi2Session *)onAppDataCallback:(SessionAppDataCallback)callback;


- (FPWCSApi2Session *)onIncomingCallCallback:(IncomingCallCallback)callback;

/**
 Get session status
 
 @return `kFPWCSSessionStatus` session status
 **/
- (kFPWCSSessionStatus)getStatus;

- (void)sendData:(NSDictionary *)data;

- (void)sendData:(NSDictionary *)data handler:(FPWCSApi2DataHandler *)handler;

@end
