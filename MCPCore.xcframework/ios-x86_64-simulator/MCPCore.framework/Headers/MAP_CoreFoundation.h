//
//  MAP_CoreFoundation.h
//  mstapnext_injectable_ios
//
//  Created by Brian on 9/4/15.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef MAP_CoreFoundation_h
#define MAP_CoreFoundation_h

#include <Foundation/Foundation.h>

#define LOGE(fmt, ...) NSLog(@"%s:%d " fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#ifndef CF_DEBUG
#define CF_DEBUG 0
#endif
#if CF_DEBUG
#define LOGI(fmt, ...) NSLog(@"%s:%d " fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define LOGI(fmt, ...)
#endif

#pragma GCC visibility push(default)

#ifdef __cplusplus
extern "C" {
#endif

void MAP_CoreFoundationInit(void);

#ifdef __cplusplus
}
#endif

#pragma GCC visibility pop

#endif /* MAP_CoreFoundation_h */
