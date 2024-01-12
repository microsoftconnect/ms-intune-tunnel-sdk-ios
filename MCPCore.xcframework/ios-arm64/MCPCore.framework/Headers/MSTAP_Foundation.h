//
//  MSTAP_Foundation.h
//  mstapnext_injectable_ios
//
//  Created on 9/29/15.
//
//

#ifndef MSTAP_Foundation_h
#define MSTAP_Foundation_h

#import <Foundation/Foundation.h>

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE
#import <objc/runtime.h>
#import <objc/message.h>
#else
#import <objc/objc-class.h>
#endif

#import "mapioslog.h"
#import "acstatus.h"
#import "NSObject+MAPSwizzle.h"
#import "MCP_Foundation.h"

#pragma GCC visibility push(default)

#ifdef __cplusplus
extern "C" {

class IMCPInterception;

void MSTAP_FoundationInit(IMCPInterception *pInterception);
void MSTAP_FoundationBlacklistInit(IMCPInterception *pInterception);
#endif

void MSTAP_FoundationEarlyInit();

#ifdef __cplusplus
}
#endif

#pragma GCC visibility pop

#endif /* MSTAP_Foundation_h */
