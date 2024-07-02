//
//  MAP_CFStream.h
//  mstapnext_injectable_ios
//
//  Created by Connor Kelley on 8/27/18.
//  Copyright © 2018 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef MAP_CFStream_h
#define MAP_CFStream_h

#include <CoreFoundation/CoreFoundation.h>
#include "MAP_NSStream.h"

#ifdef __cplusplus
extern "C" {
#endif

void MAP_CFStreamClassInit(void);

#ifdef __cplusplus
}
#endif

#endif /* MAP_CFStream_h */
