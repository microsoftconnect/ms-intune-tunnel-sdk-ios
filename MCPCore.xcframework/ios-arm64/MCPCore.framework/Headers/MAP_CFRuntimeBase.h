//
//  MAP_CFRuntimeBase.h
//  mstapnext_injectable_ios
//
//  Created by bpescatore on 9/4/15.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef MAP_CFRuntimeBase_h
#define MAP_CFRuntimeBase_h

#include <sys/types.h>
#include <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
extern "C" {
#endif

CFAllocatorRef MAP_CFAllocatorCreate(CFTypeRef infoObject);

CFTypeRef MAP_CFTypeGetInfoObject(CFTypeRef cfObject);

#ifdef __cplusplus
}
#endif

#endif /* MAP_CFRuntimeBase_h */
