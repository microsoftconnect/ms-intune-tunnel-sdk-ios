//
//  SwizzledClassDepot.h
//  MSTAPNextLink
//
//  Created by Richard Perry on 7/16/21.
//  Copyright © 2021 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#import <Foundation/Foundation.h>
__attribute__ ((visibility ("default")))
void MAP_initializeDepot();
__attribute__ ((visibility ("default")))
bool checkAndRegisterClassWithDepot(Class swizzledClass, NSString* swizzleType);

@interface SwizzledClassDepot : NSObject

@end

