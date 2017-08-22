//
//  FPWCSApi2Room.h
//  FPWCSApi2
//
//  Created by Andrey Stepanov on 27/11/2016.
//  Copyright © 2016 user. All rights reserved.
//
#import "FPWCSApi2Stream.h"
#import "FPWCSApi2Session.h"
#import <JSONModel/JSONModel.h>

@interface FPWCSApi2RoomMessage : JSONModel
@property NSString *from;
@property NSString *to;
@property NSString *text;
@property NSMutableDictionary *roomConfig;
@end

@interface FPWCSApi2RoomParticipant : NSObject
- (FPWCSApi2Stream *) play:(RTCEAGLVideoView *)display;
- (void) stop;
- (void)sendMessage:(NSString *) message;
- (NSString *)getName;
- (NSString *)getStreamName;
@end

@interface FPWCSApi2RoomOptions : NSObject
@property NSString *name;
@end

typedef NS_ENUM(NSInteger, kFPWCSRoomParticipantEvent) {
    kFPWCSRoomParticipantEventJoined,
    kFPWCSRoomParticipantEventLeft,
    kFPWCSRoomParticipantEventPublished,
};

@class FPWCSApi2Room;

typedef void (^RoomFailedCallback)(FPWCSApi2Room *, NSString *);

typedef void (^RoomStateCallback)(FPWCSApi2Room *);

typedef void (^RoomParticipantCallback)(FPWCSApi2Room *, FPWCSApi2RoomParticipant *);

typedef void (^RoomMessageCallback)(FPWCSApi2Room *, FPWCSApi2RoomMessage *);

@interface FPWCSApi2Room : NSObject

- (void)leave:(FPWCSApi2DataHandler *)handler;

- (FPWCSApi2Stream *)publish:(RTCEAGLVideoView *)display;

- (void) unpublish;

- (FPWCSApi2Room *)onFailedCallback:(RoomFailedCallback)callback;

- (FPWCSApi2Room *)onStateCallback:(RoomStateCallback)callback;

- (FPWCSApi2Room *)on:(kFPWCSRoomParticipantEvent)event
             participantCallback:(RoomParticipantCallback)callback;

- (FPWCSApi2Room *)onMessageCallback:(RoomMessageCallback)callback;

- (NSString *) getName;

- (NSDictionary *) getParticipants;

@end
