//
//  MST_WebKit.h
//  mstapnext_injectable_ios
//
//  Created by Connor Kelley on 1/31/18.
//  Copyright © 2018 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef MST_WebKit_h
#define MST_WebKit_h

#import <Foundation/Foundation.h>
#import "MCP.h"
#import "JRSwizzle.h"
#import "MAP_Foundation.h"

#ifdef __cplusplus
extern "C" {
#endif

MCP_EXPORT
void MST_WebKitInit(void);

#ifdef __cplusplus
}
#endif

MCP_EXPORT
@interface NSObject(MST_WebKit)

+ (BOOL) performSwizzle;
@end

#endif /* MST_WebKit_h */
