//
//  SFSafariViewController+MAP_SFSafariViewController.h
//  mstapnext_injectable_ios
//
//  Created by Connor Kelley on 9/5/17.
//  Copyright © 2017 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#import <SafariServices/SFSafariViewController.h>
#import "MAP_Foundation.h"

@interface SFSafariViewController (MAP_SFSafariViewController)

+ (BOOL) performSwizzle;

@end

