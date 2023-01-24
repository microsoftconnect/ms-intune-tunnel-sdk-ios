//
//  MCP_SocketStream.h
//  mstapnext_injectable_ios
//
//  Created by Connor Kelley on 1/24/19.
//  Copyright © 2019 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

// This protocol is intended to provide a way to access a plugin agnostic socket stream implementation
// It is currently solely implemented in terms of GDSocket, but we will need to create a MstapNext.Legacy.Next impl eventually
typedef NS_ENUM(NSUInteger, MCP_AffectedSocketStream) {
    MCP_SocketStreamDefault = 0,
    MCP_SocketStreamRead,
    MCP_SocketStreamWrite
};

@protocol MCP_SocketStreamDelegate <NSObject>

- (void)socketReceivedEvent:(NSStreamEvent)event;
- (void)socketReceivedEvent:(NSStreamEvent)event withAffectedStream:(MCP_AffectedSocketStream) stream;

@end

@protocol MCP_SocketStreamProvider

+ (instancetype)socketWithHost:(NSString *)host port:(UInt32)port secure:(BOOL)isSecure;
+ (void)specialDispatchOnQueue:(dispatch_queue_t) queue withBlock:(void(^)())theBlock;
- (BOOL) disableHostVerification;
- (BOOL) disablePeerVerification;
- (void) setDelegate:(id<MCP_SocketStreamDelegate>)delegate;

// NSStream Overrides
- (void)open;
- (void)close;

- (void) scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSRunLoopMode)mode;
- (void) removeFromRunLoop:(NSRunLoop *)aRunLoop forMode:(NSRunLoopMode)mode;

- (id)propertyForKey:(NSStreamPropertyKey)key;
- (BOOL)setProperty:(id)property forKey:(NSStreamPropertyKey)key;

- (NSStreamStatus) streamStatus;
- (NSError *)streamError;

// NSInputStream Overrides
- (BOOL)hasBytesAvailable;
- (NSInteger)read:(uint8_t *)data maxLength:(NSUInteger)len;
- (BOOL)getBuffer:(uint8_t * _Nullable *)buffer length:(nonnull NSUInteger *)len;

// NSOutputStream Overrides
- (BOOL)hasSpaceAvailable;
- (NSInteger)write:(const uint8_t *)data maxLength:(NSUInteger)len;

-(CFRunLoopRef) currentRunLoop;

@end

@interface NSStream (MCP_SocketStream)

+ (BOOL)registerSocketStreamProvider:(Class)streamProvider;
+ (BOOL)unregisterSocketStreamProvider:(Class)streamProvider;
+ (Class<MCP_SocketStreamProvider>)getSocketStreamProvider;

@end


