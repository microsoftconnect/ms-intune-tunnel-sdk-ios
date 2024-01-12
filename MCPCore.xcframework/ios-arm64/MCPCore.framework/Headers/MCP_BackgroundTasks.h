//
//  MCP_BackgroundTasks.h
//  mstapnext_injectable_ios
//
//  Created by Connor Kelley on 9/3/20.
//  Copyright © 2020 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef MCP_BackgroundTasks_h
#define MCP_BackgroundTasks_h

#import <Foundation/Foundation.h>
#import "MCP.h"
#import "JRSwizzle.h"
#import "MAP_Foundation.h"

#ifdef __cplusplus
extern "C" {
#endif

MCP_EXPORT
void MCP_BackgroundTasksInit(void);

#ifdef __cplusplus
}
#endif

MCP_EXPORT
@interface NSObject(MCP_BackgroundTasks)

+ (BOOL) performSwizzle;
@end

#endif /* MCP_BackgroundTask_h */
