//
//  IosKeychainRelinks.h
//  MSTAPNextLink
//
//  Created by Richard Perry on 4/15/21.
//  Copyright © 2021 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#import <Foundation/Foundation.h>
#include "MstapNextServerCertProvider.h"
#import "IosKeychainMonitor.h"

#pragma GCC visibility push(default)

void MAP_KeychainRelinkInit();

#pragma GCC visibility pop

@interface IosKeychainRelinks : NSObject

@end
