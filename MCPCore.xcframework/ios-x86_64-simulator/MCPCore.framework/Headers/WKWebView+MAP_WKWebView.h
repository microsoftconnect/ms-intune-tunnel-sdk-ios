//
//  WKWebView+MAP_WKWebView.h
//  mstapnext_injectable_ios
//
//  Created by Connor Kelley on 9/5/17.
//  Copyright © 2017 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//


#import <TargetConditionals.h>
#import <Foundation/Foundation.h>
#import <WebKit/WKWebView.h>

@interface WKWebView (MAP_WKWebView)

+ (BOOL) performSwizzle;
    
@end
