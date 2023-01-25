//
//  NSURLProtocol+MCP_WKWebViewAuthentication.h
//  MSTAPNextLink
//
//  Created by Connor Kelley on 6/22/20.
//  Copyright © 2020 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#import <Foundation/Foundation.h>
#import "NSObject+MAPSwizzle.h"

NS_ASSUME_NONNULL_BEGIN

@interface NSURLProtocol (MCP_WKWebViewAuthentication)

+ (BOOL) interceptAuthenticationRequests;

@end

NS_ASSUME_NONNULL_END
