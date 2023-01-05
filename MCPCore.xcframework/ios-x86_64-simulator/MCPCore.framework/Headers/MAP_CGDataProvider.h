//
//  MAP_CGDataProvider.h
//  mstapnext_injectable_ios
//
//  Created by Vadim Lozko on 1/25/17.
//  Copyright © 2017 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#import <CoreGraphics/CoreGraphics.h>

#pragma GCC visibility push(default)

#ifdef __cplusplus
extern "C" {
#endif

CGDataProviderRef MAP_CGDataProviderCreateWithURL(CFURLRef url);

void MAP_CGDataProviderClassInit(void);

#ifdef __cplusplus
}
#endif

#pragma GCC visibility pop
