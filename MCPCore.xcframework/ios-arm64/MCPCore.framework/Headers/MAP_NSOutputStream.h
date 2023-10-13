//
//  MAP_NSOutputStream.h
//  MAP-iOS
//
//  Created by Brian on 10/14/15.
//  Licensed to Microsoft under Contract #7267038.
//

#import <Foundation/Foundation.h>
#import "MAP_NSStream.h"

__attribute__ ((visibility ("default")))
@interface MAP_NSOutputStream_File : MAP_NSStream_File

- (nullable instancetype)initToFileAtPath:(NSString *)path append:(BOOL)shouldAppend;

@end

@interface MAP_NSOutputStream_Sock : MAP_NSStream_Sock

// Required overrides
- (NSInteger)write:(const uint8_t *)buffer maxLength:(NSUInteger)len;
- (BOOL) hasSpaceAvailable;

@end

