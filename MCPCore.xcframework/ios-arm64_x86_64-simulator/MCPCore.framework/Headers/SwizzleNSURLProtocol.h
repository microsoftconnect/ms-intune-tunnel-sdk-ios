//
//  NSURLProtocol+SwizzleNSURLProtocol.h
//  mstapnext_injectable_ios
//
//  Created by Brian Pescatore on 4/19/16.
//  Copyright © 2016 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#import <Foundation/Foundation.h>

@interface NSURLProtocol (SwizzleNSURLProtocol)

+ (BOOL)performSwizzle;

@end
