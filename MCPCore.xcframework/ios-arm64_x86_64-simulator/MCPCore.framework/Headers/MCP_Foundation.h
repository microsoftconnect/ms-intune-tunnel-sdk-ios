//
//  MCP_Foundation.h
//  MSTAPNextLink
//
//  Created by Tim Champagne Jr. on 9/26/18.
//  Copyright © 2018 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef MCP_Foundation_h
#define MCP_Foundation_h

#import <Foundation/Foundation.h>

#import "MCP.h"
#import "acstatus.h"
#import "mapioslog.h"

MCP_BEGIN_EXPORT()

#ifdef __cplusplus
extern "C" {

class IMCPInterception;

void MCP_FoundationInit(IMCPInterception *pInterception);
void MCP_FoundationBlacklistInit(IMCPInterception *pInterception);
#endif

// could rename this to something like MAP_shouldInterceptFileURL to avoid confusion
ACSTATUS MAP_shouldInterceptURL(NSURL * url);

ACSTATUS MAP_shouldInterceptFilePath(NSString * path);

ACSTATUS MAP_shouldInterceptWebURL(NSURL *url);

ACSTATUS MAP_shouldInterceptAnyURL(NSURL * url);

void MAP_addPathToWhitelist(NSString *path);
void MAP_addPathsToWhitelist(NSArray<NSString*> *paths);

#ifdef __cplusplus
}
#endif

#define MAP_LOG_DEBUG(fmt, args...) \
MAPIOSLogDebug(ACLC_EXT_FOUNDATION, @"%s " fmt, __PRETTY_FUNCTION__, ##args)

#define MAP_LOG_DEBUGTICK() MAP_LOG_DEBUG(@"")

#define MAP_LOG_INFO(fmt, args...) \
MAPIOSLogInfo(ACLC_EXT_FOUNDATION, @"%s " fmt, __PRETTY_FUNCTION__, ##args)

#define MAP_LOG_WARN(fmt, args...) \
MAPIOSLogWarn(ACLC_EXT_FOUNDATION, @"%s " fmt, __PRETTY_FUNCTION__, ##args)

#define MAP_LOG_MINOR(fmt, args...) \
MAPIOSLogMinor(ACLC_EXT_FOUNDATION, @"%s " fmt, __PRETTY_FUNCTION__, ##args)

#define MAP_LOG_MAJOR(fmt, args...) \
MAPIOSLogMajor(ACLC_EXT_FOUNDATION, @"%s " fmt, __PRETTY_FUNCTION__, ##args)

#define MAP_LOG_CRITICAL(fmt, args...) \
MAPIOSLogCritical(ACLC_EXT_FOUNDATION, @"%s " fmt, __PRETTY_FUNCTION__, ##args)

#define CDSQL_LOG_DEBUG(fmt, args...) \
MAPIOSLogDebug(ACLC_EXT_SQLCIPHER, @"%s " fmt, __PRETTY_FUNCTION__, ##args)

#define CDSQL_LOG_WARN(fmt, args...) \
MAPIOSLogWarn(ACLC_EXT_SQLCIPHER, @"%s " fmt, __PRETTY_FUNCTION__, ##args)

MCP_END_EXPORT()

#endif /* MCP_Foundation_h */
