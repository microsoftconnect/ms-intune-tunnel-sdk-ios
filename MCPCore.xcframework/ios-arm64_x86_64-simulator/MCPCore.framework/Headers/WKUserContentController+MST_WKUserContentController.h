//
//  WKUserContentController+MST_WKUserContentController.h
//  MSTAPNextLink
//
//  Created by Connor Kelley on 1/31/18.
//  Copyright © 2018 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#import <WebKit/WebKit.h>

@interface WKUserContentController (MST_WKUserContentController)

+(BOOL)performSwizzle;

-(void)addMSTScript:(WKUserScript *)script;

@end
