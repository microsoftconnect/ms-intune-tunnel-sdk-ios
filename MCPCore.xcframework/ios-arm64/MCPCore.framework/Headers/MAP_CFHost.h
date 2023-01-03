//
//  MAP_CFHost.h
//  MAP-iOS
//
//  Created on 10/8/15.
//
//

/**
 * @file MAP_CFHost.h
 *
 * Contains a secure, API-compatable implementation of CFHost.
 * See <a href="https://developer.apple.com/library/prerelease/ios/documentation/CoreFoundation/Reference/CFHostRef/index.html">CFHost</a>
 * for more informtion on general API usage.
 */

#ifndef MAP_CFHost_h
#define MAP_CFHost_h

#include <CoreFoundation/CoreFoundation.h>
#include <CFNetwork/CFHost.h>

#ifdef __cplusplus
extern "C" {
#endif

void MAP_CFHostClassInit(void);

#ifdef __cplusplus
}
#endif

#endif /* MAP_CFHost_h */
