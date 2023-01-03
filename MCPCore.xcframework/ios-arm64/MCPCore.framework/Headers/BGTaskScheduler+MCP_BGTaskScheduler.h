//
//  BGTaskScheduler+MCP_BGTaskScheduler.h
//  MSTAPNextLink
//
//  Created by Connor Kelley on 9/2/20.
//  Copyright © 2020 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#import <BackgroundTasks/BackgroundTasks.h>

NS_ASSUME_NONNULL_BEGIN

@interface BGTaskScheduler (MCP_BGTaskScheduler)

+ (BOOL)performSwizzle;

@end

NS_ASSUME_NONNULL_END
