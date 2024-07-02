//
//  MAP_NSCFInputStream.h
//  mstapnext_injectable_ios
//
//  Created on 9/29/15.
//  Licensed to Microsoft under Contract #7267038.
//

#import <Foundation/Foundation.h>
#import "MAP_NSStream.h"

__attribute__ ((visibility ("default")))
@interface MAP_NSInputStream_File : MAP_NSStream_File

- (instancetype)initWithFileAtPath:(NSString *)path;

@end

@interface MAP_NSInputStream_Prox : MAP_NSStream

@property CFTypeRef cfSelf;

- (instancetype)initWithCFRequest:(CFHTTPMessageRef)request CFStreamBody:(CFReadStreamRef)body;

- (BOOL)hasBytesAvailable;
- (NSUInteger)read:(UInt8 *)bytes maxLength:(NSUInteger)length;

- (BOOL)setCFCallbackForEvents:(CFOptionFlags)events clientCallback:(CFReadStreamClientCallBack)callback clientContext:(CFStreamClientContext *)clientContext;

@end

@interface MAP_NSInputStream_Sock : MAP_NSStream_Sock

- (BOOL)hasBytesAvailable;
- (NSInteger)read:(UInt8 *)bytes maxLength:(NSUInteger)length;
- (BOOL)getBuffer:(uint8_t * _Nullable *)buffer length:(NSUInteger *)len;

@end
