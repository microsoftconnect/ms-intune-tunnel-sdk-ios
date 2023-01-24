//
//  MSTAP_HTTPCacheFixup.h
//  mstapnext_injectable_ios
//
//  Created by Brian Pescatore on 11/5/15.
//  Licensed to Microsoft under Contract #7267038.
//

#import <Foundation/Foundation.h>

@interface MSTAP_HTTPCacheFixup : NSURLProtocol

+ (void) registerProtocol;

@end
