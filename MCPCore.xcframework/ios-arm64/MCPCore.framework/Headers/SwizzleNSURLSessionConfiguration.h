//
//  SwizzleNSURLSessionConfiguration.h
//  mstapnext_injectable_ios
//
//  Created by Sujan Kota on 10/30/15.
//  Copyright © 2015 Mocana. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#import <Foundation/Foundation.h>

#ifndef MapPolicySwizzler_SwizzleNSURLSessionConfiguration_h
#define MapPolicySwizzler_SwizzleNSURLSessionConfiguration_h

void forceLinkNSURLSessionConfiguration(void);

@interface NSURLSessionConfiguration (MAP_NSURLSessionConfiguration)

+ (void)mapInitNSURLSessionConfiguration;

+ (void)registerURLProtocolClass:(Class)cls;
+ (BOOL)unregisterURLProtocolClass:(Class)cls;

@end


#endif /* MapPolicySwizzler_SwizzleNSURLSessionConfiguration_h */
