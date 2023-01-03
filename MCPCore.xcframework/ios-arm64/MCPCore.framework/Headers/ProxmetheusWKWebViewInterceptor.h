//
//  ProxmetheusWKWebViewInterceptor.h
//  Proxmetheus
//
//  Created by Connor Kelley on 1/19/18.
//  Copyright © 2018 BlueCedar. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WebKit/WebKit.h>

@interface ProxmetheusWKWebViewInterceptor : WKWebViewConfiguration <WKScriptMessageHandler>

-(WKWebViewConfiguration *)getConfiguration:(WKWebViewConfiguration *)existingConfig;

@end
