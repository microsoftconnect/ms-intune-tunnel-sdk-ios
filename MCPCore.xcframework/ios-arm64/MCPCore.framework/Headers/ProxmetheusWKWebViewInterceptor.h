//
//  ProxmetheusWKWebViewInterceptor.h
//  Proxmetheus
//
//  Created by Connor Kelley on 1/19/18.
//  Copyright © 2018 BlueCedar. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#import <Foundation/Foundation.h>
#import <WebKit/WebKit.h>

@interface ProxmetheusWKWebViewInterceptor : WKWebViewConfiguration <WKScriptMessageHandler>

-(instancetype) initWithWebView:(WKWebView* )webView;
-(WKWebViewConfiguration *)getConfiguration:(WKWebViewConfiguration *)existingConfig;

@end
