//
//  MCPCommon.h
//  MCPCommon
//
//  Created by Tim Champagne Jr. on 4/19/19.
//  Copyright © 2019 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef _MCP_COMMON_H_
#define _MCP_COMMON_H_

#ifdef __OBJC__

#import "JRSwizzle.h"
#import "MAPSwizzleClassMethod.h"
#import "NSObject+MAPSwizzle.h"
#import "SwizzledClassDepot.h"

//! Project version number for MCPCommon.
FOUNDATION_EXPORT double MCPCommonVersionNumber;

//! Project version string for MCPCommon.
FOUNDATION_EXPORT const unsigned char MCPCommonVersionString[];

#endif  // __OBJC__

// In this header, you should import all the public headers of your framework using statements like #import <MCPCommon/PublicHeader.h>

#import "mberrors.h"
#import "bypass.h"
#import "Relinker.h"
#import "MCP.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma GCC visibility push(default)

extern const unsigned int kMCPTestSymbol;

#pragma GCC visibility pop

#ifdef __cplusplus
}
#endif

#endif  // _MCP_COMMON_H_
