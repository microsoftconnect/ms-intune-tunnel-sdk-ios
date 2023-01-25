//
//  SocketStreamConnectorBase.h
//  MSTAPNextLink
//
//  Created by Richard Perry on 3/13/19.
//  Copyright © 2019 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#import <Foundation/Foundation.h>
#import "NSStream+MCP_SocketStream.h"

typedef enum : NSUInteger {
    SocketStreamActivityHandshakeFinished,
    SocketStreamActivitySignalRead,
    SocketStreamActivitySignalWrite,
    SocketStreamActivitySignalConnect
} SocketStreamActivity;

typedef enum : NSUInteger {
    Ready,
    NotReady,
    Waiting
} ioStatus;

@protocol SocketStreamConnectorDelegate <NSObject>

-(void) socketStreamActivitySignaled:(SocketStreamActivity) activity;

@end

@interface SocketStreamConnectorBase : NSObject
@property(weak, nonatomic) id<SocketStreamConnectorDelegate> delegate;
-(instancetype) initWithHost:(NSString*) host withBackingSocket:(CFSocketRef) backingSocket;
- (NSInteger)read:(uint8_t *)data maxLength:(NSUInteger)len;
- (NSInteger)write:(const uint8_t *)data maxLength:(NSUInteger)len;
-(void) close;
-(NSError*) getError;
-(BOOL)connectSocket;
-(ioStatus)handleReadCallback;
-(ioStatus)handleWriteCallback;
-(BOOL)handleConnectCallback;

@end
