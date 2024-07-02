//
//  MAP_NSStream.h
//  mstapnext_injectable_ios
//
//  Created by Vadim Lozko on 1/25/16.
//  Copyright © 2016 Mocana. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#import <Foundation/Foundation.h>
#import "NSStream+MCP_SocketStream.h"

@interface MAP_NSStream : NSObject

@property NSStreamStatus streamStatus;
@property (strong) NSError *streamError;
@property (weak) id <NSStreamDelegate> delegate;
@property BOOL isScheduledInRunLoop;

//To be subclasses
- (void)open;
- (void)close;

- (BOOL)setProperty:(id)property forKey:(NSString *)key;
- (id)propertyForKey:(NSString *)key;

- (void)scheduleInRunLoop:(NSRunLoop *)runLoop forMode:(nonnull NSString *)mode;
- (void)removeFromRunLoop:(NSRunLoop *)runLoop forMode:(nonnull NSString *)mode;

- (void)scheduleInCFRunLoop:(CFRunLoopRef)runLoop forMode:(CFStringRef)mode;
- (void)removeFromCFRunLoop:(CFRunLoopRef)runLoop forMode:(CFStringRef)mode;

- (void)dispatchEvent:(NSStreamEvent)event;

- (void)performStreamClientCallbackForEvent:(NSStreamEvent)event;

@end

@interface MAP_NSStream_File : MAP_NSStream

@property (strong) NSString *path;
@property FILE *file;

- (MAP_NSStream_File *)initWithPath:(NSString *)path;
- (void)openForMode:(NSString *)mode;

@end

@interface MAP_SocketStreamPair : NSObject <MCP_SocketStreamDelegate>

@property (nonatomic, assign) CFRunLoopRef runLoop;
// Set to weak so these can properly deallocate
@property (nonatomic, weak) NSInputStream *inputStream;
@property (nonatomic, weak) NSOutputStream *outputStream;
@property (nonatomic, strong) NSObject<MCP_SocketStreamProvider> *socketStream;

- (void)openSocket;
- (void)closeSocket;

- (BOOL)hasSpaceAvailable;
- (BOOL)hasBytesAvailable;

- (void)scheduleSocketInRunLoop:(NSRunLoop *)runloop forMode:(NSRunLoopMode)mode;
- (void)removeSocketFromRunLoop:(NSRunLoop *)runloop forMode:(NSRunLoopMode)mode;

- (BOOL)setProperty:(id)property forKey:(NSString *)key;
- (id) propertyForKey:(NSString *)key;

- (NSInteger)read:(uint8_t *)buffer maxLength:(NSUInteger)len;
- (NSInteger)write:(const uint8_t *)buffer maxLength:(NSUInteger)len;

- (instancetype)initWithHost:(NSString *)host port:(UInt32)port;
- (void)bindReadStream:(CFReadStreamRef *)pReadStream writeStream:(CFWriteStreamRef *)pWriteStream;
@end


@interface MAP_NSStream_Sock : MAP_NSStream

@property (nonatomic, strong) MAP_SocketStreamPair *socketPair;
@property (nonatomic, strong) dispatch_queue_t queue;
@property (nonatomic, strong) NSRunLoop *runLoop;

- (void)setDispatchQueue:(dispatch_queue_t) queue;
- (instancetype)initWithPair:(MAP_SocketStreamPair *)pair;

@end
