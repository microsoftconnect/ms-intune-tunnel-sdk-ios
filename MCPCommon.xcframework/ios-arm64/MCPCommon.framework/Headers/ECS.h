//
//  ECS.h
//
//  Created by Todd Bohman on 7/3/24.
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//

#import <Foundation/Foundation.h>

__attribute__ ((visibility ("default")))
@interface ECS : NSObject

+(ECS*)sharedInstance;

-(BOOL)urlSchemeHandlerEnabled;
-(BOOL)mamServiceUrlBypassEnabled;
-(BOOL)loginServiceUrlBypassEnabled;
-(BOOL)reloadRedirectsEnabled;
-(BOOL)webSocketsEnabled;
-(BOOL)urlCacheEnabled;
-(BOOL)useDataTaskDelegate;

-(NSString*)webViewJSON;

-(void)fetchIfNeeded;

-(void)setUPN:(NSString *)upn;

@end
