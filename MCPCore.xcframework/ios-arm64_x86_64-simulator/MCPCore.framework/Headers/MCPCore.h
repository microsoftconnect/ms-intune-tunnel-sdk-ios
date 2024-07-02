//
//  MCPCommon.h
//  MCPCommon
//
//  Created by Tim Champagne Jr. on 4/19/19.
//  Copyright © 2019 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef _MCP_CORE_H_
#define _MCP_CORE_H_

#import <Foundation/Foundation.h>

//! Project version number for MCPCommon.
FOUNDATION_EXPORT double MCPCoreVersionNumber;

//! Project version string for MCPCommon.
FOUNDATION_EXPORT const unsigned char MCPCoreVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <MCPCommon/PublicHeader.h>

// #import <MCPCore/IosMCPPolicyBridge.h>
#import "mapio.h"
#import "mapio_ios.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma GCC visibility push(default)


#pragma GCC visibility pop

#ifdef __cplusplus
}
#endif

#endif  // _MCP_CORE_H_
