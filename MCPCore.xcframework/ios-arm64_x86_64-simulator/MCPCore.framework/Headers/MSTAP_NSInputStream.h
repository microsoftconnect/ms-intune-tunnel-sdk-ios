//
//  MSTAP_NSCFInputStream.h
//  mstapnext_injectable_ios
//
//  Created on 9/29/15.
//  Licensed to Microsoft under Contract #7267038.
//

#import <Foundation/Foundation.h>
#import "MSTAP_NSStream.h"

__attribute__ ((visibility ("default")))
@interface MSTAP_NSInputStream_File : MSTAP_NSStream_File

- (instancetype)initWithFileAtPath:(NSString *)path;

@end

@interface MSTAP_NSInputStream_Prox : MSTAP_NSStream

@property CFTypeRef cfSelf;

- (instancetype)initWithCFRequest:(CFHTTPMessageRef)request CFStreamBody:(CFReadStreamRef)body;

- (BOOL)hasBytesAvailable;
- (NSUInteger)read:(UInt8 *)bytes maxLength:(NSUInteger)length;

- (BOOL)setCFCallbackForEvents:(CFOptionFlags)events clientCallback:(CFReadStreamClientCallBack)callback clientContext:(CFStreamClientContext *)clientContext;

@end

@interface MSTAP_NSInputStream_Sock : MSTAP_NSStream_Sock

- (BOOL)hasBytesAvailable;
- (NSInteger)read:(UInt8 *)bytes maxLength:(NSUInteger)length;
- (BOOL)getBuffer:(uint8_t * _Nullable *)buffer length:(NSUInteger *)len;

@end
