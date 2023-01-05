//
//  MAP_CFSocket.h
//  MAP-iOS
//
//  Created on 10/13/15.
//  Licensed to Microsoft under Contract #7267038.
//

/**
 * @file MAP_CFSocket.h
 *
 * Contains a secure, API-compatable implementation of CFSocket.h.
 * See <a href="https://developer.apple.com/library/prerelease/ios/documentation/CoreFoundation/Reference/CFSocketRef/index.html">CFSocket</a>
 * for more informtion on general API usage.
 */

#ifndef MAP_CFSocket_h
#define MAP_CFSocket_h

#ifdef __cplusplus
extern "C" {
#endif

#pragma GCC visibility push(default)

void MAP_CFSocketClassInit(void);

CFSocketRef
MAP_CFSocketCreate(CFAllocatorRef allocator, SInt32 protocolFamily, SInt32 socketType, SInt32 protocol,
                   CFOptionFlags callBackTypes, CFSocketCallBack callout,
                   const CFSocketContext *context);
CFSocketRef
MAP_CFSocketCreateWithNative(CFAllocatorRef allocator, CFSocketNativeHandle sock,
                             CFOptionFlags callBackTypes, CFSocketCallBack callout,
                             const CFSocketContext *context);
CFSocketRef
MAP_CFSocketCreateWithSocketSignature(CFAllocatorRef allocator, const CFSocketSignature *signature,
                                      CFOptionFlags callBackTypes, CFSocketCallBack callout,
                                      const CFSocketContext *context);
CFSocketRef
MAP_CFSocketCreateConnectedToSocketSignature(CFAllocatorRef allocator, const CFSocketSignature *signature,
                                             CFOptionFlags callBackTypes, CFSocketCallBack callout,
                                             const CFSocketContext *context, CFTimeInterval timeout);


CFDataRef
MAP_CFSocketCopyAddress(CFSocketRef s);

CFDataRef
MAP_CFSocketCopyPeerAddress(CFSocketRef s);

void
MAP_CFSocketDisableCallBacks(CFSocketRef s, CFOptionFlags callBackTypes);

void
MAP_CFSocketEnableCallBacks(CFSocketRef s, CFOptionFlags callBackTypes);

void
MAP_CFSocketGetContext(CFSocketRef s, CFSocketContext *context);

CFSocketNativeHandle
MAP_CFSocketGetNative(CFSocketRef s);

CFOptionFlags
MAP_CFSocketGetSocketFlags(CFSocketRef s);

CFSocketError
MAP_CFSocketSetAddress(CFSocketRef s, CFDataRef address);

void
MAP_CFSocketSetSocketFlags(CFSocketRef s, CFOptionFlags flags);

CFSocketError
MAP_CFSocketConnectToAddress(CFSocketRef s, CFDataRef address, CFTimeInterval timeout);

CFRunLoopSourceRef
MAP_CFSocketCreateRunLoopSource(CFAllocatorRef allocator, CFSocketRef s, CFIndex order);

CFTypeID
MAP_CFSocketGetTypeID(void);

void
MAP_CFSocketInvalidate(CFSocketRef s);

Boolean
MAP_CFSocketIsValid(CFSocketRef s);

CFSocketError
MAP_CFSocketSendData(CFSocketRef s, CFDataRef address, CFDataRef data, CFTimeInterval timeout);

#pragma GCC visibility pop

#ifdef __cplusplus
}
#endif

#endif /* MAP_CFSocket_h */
