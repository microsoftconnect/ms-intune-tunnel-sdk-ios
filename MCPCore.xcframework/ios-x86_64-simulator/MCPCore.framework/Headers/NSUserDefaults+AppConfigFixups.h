//
//  NSUserDefaults+AppConfigFixups.h
//  MSTAPNextLink
//
//  Created by Connor Kelley on 2/18/21.
//  Copyright © 2021 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#import <Foundation/Foundation.h>
#import "NSObject+MAPSwizzle.h"

NS_ASSUME_NONNULL_BEGIN

@interface NSUserDefaults (AppConfigFixups)

+ (BOOL)performSwizzle;

@end

NS_ASSUME_NONNULL_END
