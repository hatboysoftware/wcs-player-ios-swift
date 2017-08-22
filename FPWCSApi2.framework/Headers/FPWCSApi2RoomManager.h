//
//  FPWCSApi2RoomManager.h
//  FPWCSApi2
//
//  Created by Andrey Stepanov on 28/11/2016.
//  Copyright © 2016 user. All rights reserved.
//

#import "FPWCSApi2Room.h"
#import "FPWCSApi2Session.h"
#import "FPWCSApi2Model.h"

@interface FPWCSApi2RoomManagerOptions : NSObject
@property NSString *urlServer;
@property NSString *username;
@end

typedef NS_ENUM(NSInteger, kFPWCSRoomManagerEvent) {
    kFPWCSRoomManagerEventConnected,
    kFPWCSRoomManagerEventDisconnected,
    kFPWCSRoomManagerEventFailed
};

@class FPWCSApi2RoomManager;

typedef void (^RoomManagerEventCallback)(FPWCSApi2RoomManager *);

@interface FPWCSApi2RoomManager : NSObject

+ (NSString *)roomManagerEventToString:(kFPWCSRoomManagerEvent)status;

- (FPWCSApi2Room *)join:(FPWCSApi2RoomOptions *) options;

- (void) disconnect;

- (FPWCSApi2Room *)on:(kFPWCSRoomManagerEvent)event
             callback:(RoomManagerEventCallback)callback;

- (NSString *) getUsername;

- (FPWCSApi2Session *) getSession;

@end

