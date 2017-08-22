//
//  FPWCSApi2Call.h
//  FPWCSApi2
//
//  Created by Andrey Stepanov on 21/12/2016.
//  Copyright © 2016 user. All rights reserved.
//

#import "FPWCSApi2Model.h"

@class FPWCSApi2Call;

typedef void (^CallCallback)(FPWCSApi2Call *);
typedef void (^IncomingCallCallback)(FPWCSApi2Call *);

@interface FPWCSApi2Call : NSObject

-(void)call;

-(void)answer;

-(void)hangup;

-(void)hold;

-(void)unhold;

- (void) muteAudio;

- (void) unmuteAudio;

- (void) muteVideo;

- (void) unmuteVideo;

/**
 Switch camera back/front
 **/
- (void)switchCamera;

- (BOOL)isAudioMuted;

- (BOOL)isVideoMuted;

- (FPWCSApi2Call *)on:(kFPWCSCallStatus)event
               callback:(CallCallback)callback;

-(NSString *)getId;

-(BOOL)isIncoming;

-(kFPWCSCallStatus)getStatus;

-(NSString *) getCaller;

-(NSString *) getCallee;

-(NSString *) getVisibleName;

-(FPWCSApi2MediaConstraints *) getLocalConstraints;

-(FPWCSApi2MediaConstraints *) getRemoteConstraints;

-(void) setLocalDisplay:(RTCEAGLVideoView *) display;

-(void) setRemoteDisplay:(RTCEAGLVideoView *) display;

@end
