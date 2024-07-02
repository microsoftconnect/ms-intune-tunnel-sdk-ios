//
//  MAP_CFReadStream.h
//  MAP-iOS
//
//  Created by bpescatore on 9/4/15.
//  Licensed to Microsoft under Contract #7267038.  
//

/**
 * @file MAP_CFReadStream.h
 *
 * Contains a secure, API-compatable implementation of CFReadStream.
 * See <a href="https://developer.apple.com/library/prerelease/ios/documentation/CoreFoundation/Reference/CFReadStreamRef/index.html">CFReadStream</a>
 * for more informtion on general API usage.
 */

#ifndef MAP_CFReadStream_h
#define MAP_CFReadStream_h

#include <CoreFoundation/CoreFoundation.h>
#include <CFNetwork/CFNetwork.h>

#ifdef __cplusplus
extern "C" {
#endif

@class MAP_NSInputStream_Prox;

void MAP_CFReadStreamClassInit(void);

#ifdef __cplusplus
}
#endif

#endif /* MAP_CFReadStream_h */
