//
//  MSTAPNextPluginSwiftSupport.h
//  MSTAPNextPluginSwiftSupport
//
//  Created by Richard Perry on 6/29/21.
//  Copyright © 2021 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#import <Foundation/Foundation.h>

//! Project version number for MSTAPNextPluginSwiftSupport.
FOUNDATION_EXPORT double MSTAPNextPluginSwiftSupportVersionNumber;

//! Project version string for MSTAPNextPluginSwiftSupport.
FOUNDATION_EXPORT const unsigned char MSTAPNextPluginSwiftSupportVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <MSTAPNextPluginSwiftSupport/PublicHeader.h>

// #include "mapio_ios.h"

#import "MstapNextSwiftSupport.h"

#ifdef __cplusplus
extern "C" {
#endif
    __attribute__ ((visibility ("default")))
    int UIApplicationMainMAP(int argc, char *argv[],
                             NSString *principalClassName,
                             NSString *delegateClassName);
#ifdef __cplusplus
}
#endif
