//
//  FPWCSApi2Stream.h
//  FPWCSApi
//
//  Created by user on 17/10/2016.
//  Copyright © 2016 user. All rights reserved.
//

#import "FPWCSApi2Model.h"

@class FPWCSApi2Stream;

/**
 Stream callback block.
 **/
typedef void (^StreamCallback)(FPWCSApi2Stream *);

/**
 Represents media stream.
 **/
@interface FPWCSApi2Stream : NSObject

/**
 Get stream id.
 
 @return `NSString` stream id
 **/
- (NSString *)getStreamID;

/**
 Get stream name.
 
 @return `NSString` stream name
 **/
- (NSString *)getName;

/**
 Get record stream file name.
 
 @return `NSString` stream name
 **/
- (NSString *)getRecordName;

/**
 Play stream.
 
 @param error `NSError` object to fill with info if error occurs
 **/
- (BOOL)play:(NSError **)error;

/**
 Publish stream.
 
 @param error `NSError` object to fill with info if error occurs
 **/
- (BOOL)publish:(NSError **)error;

/**
 Stop stream.
 
 @param error `NSError` object to fill with info if error occurs
 **/
- (BOOL)stop:(NSError **)error;

/**
 Is stream published.
 
 @return `BOOL` true if stream published
 **/
- (BOOL)isPublished;

/**
 Get remote bitrate reported by server, works only for subscribe Stream
 **/
- (long)getRemoteBitrate;

/**
 Get network bandwidth reported by server, works only for subscribe Stream
 **/
- (long)getNetworkBandwidth;

/**
 Get stream status.
 
 @return `kFPWCSStreamStatus` stream status
 **/
- (kFPWCSStreamStatus)getStatus;

/**
 Mute outgoing audio
 **/
- (void) muteAudio;

/**
 Unmute outgoing audio
 **/
- (void) unmuteAudio;

/**
Enable/disable loud speaker
**/
- (void)setLoudspeakerStatus:(bool) enable withError:(NSError **)error;

/**
 Mute outgoing video
 **/
- (void) muteVideo;

/**
 Unmute outgoing video
 **/
- (void) unmuteVideo;

/**
 Switch camera back/front
 **/
- (void)switchCamera;

/**
 Lock camera orientation
 **/
- (void)lockCameraOrientation;

/**
 Unlock camera orientation
 **/
- (void)unlockCameraOrientation;

/**
 Check outgoing audio mute state
 
 @return true if audio is muted or not available
 **/
- (BOOL)isAudioMuted;

/**
 Check outgoing video mute state
 
 @return true if video is muted or not available
 **/
- (BOOL)isVideoMuted;

/**
 Add stream event callback.
 
 @param event `kFPWCSStreamStatus` event type
 
 @param callback `StreamCallback` callback block
 
 @return `FPWCSApi2Stream` stream
 **/
- (FPWCSApi2Stream *)on:(kFPWCSStreamStatus)event
                callback:(StreamCallback)callback;

@end
