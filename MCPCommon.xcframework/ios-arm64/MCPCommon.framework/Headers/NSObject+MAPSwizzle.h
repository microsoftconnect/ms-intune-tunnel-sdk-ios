//
//  NSObject+MAPSwizzle.h
//  mstapnext_injectable_ios
//
//  Created by Tim Champagne Jr. on 4/12/17.
//  Copyright © 2017 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#import <objc/runtime.h>

#import <Foundation/Foundation.h>

#import "JRSwizzle.h"

#define SWIZZLE_CLASSMETHOD(method, prefix, err)                    \
if (NO == [[self class] jr_swizzleClassMethod:@selector(method) \
withClassMethod:@selector(prefix##method) error:&err]) {    \
NSLog(@"%@", err); return NO; }

#define SWIZZLE_METHOD(method, prefix, err)                         \
if ( NO ==[[self class] jr_swizzleMethod:@selector(method)      \
withMethod:@selector(prefix##method) error:&err]) {         \
    NSLog(@"%@", err); return NO; \
}

#define ASSERTING_MULTI_CLASS_METHOD_SWIZZLE(origClass, altClass, orSelector, altSelector, origMethod, altMethod, fatalMsg)                         \
if (!origClass) { \
    fatalMsg = @"Original class not found!"; \
    NSAssert(origClass != nil, fatalMsg); \
} else if (!altClass) { \
    fatalMsg = @"Alternate class not found"; \
    NSAssert(altClass != nil, fatalMsg); \
} \
if (!origMethod) { \
    BOOL isClass = object_isClass(origClass); \
    fatalMsg = [NSString stringWithFormat:@"original method %@ not found for class %@", NSStringFromSelector(orSelector), isClass ? origClass : [origClass class]]; \
    NSAssert(origMethod != nil, fatalMsg); \
} else if (!altMethod) { \
    BOOL isClass = object_isClass(altClass); \
    fatalMsg = [NSString stringWithFormat:@"alternate method %@ not found for class %@", NSStringFromSelector(altSelector), isClass ? altClass : [altClass class]]; \
    NSAssert(altMethod != nil, fatalMsg); \
} \
{\
    IMP altImp = method_getImplementation(altMethod); \
    [NSObject replaceMethodSelector:orSelector ofClass:origClass withImp:altImp andMethod:origMethod];\
}

#define SWIZZLE_INIT(method, newMethod, err)                         \
if ( NO ==[[self class] jr_swizzleMethod:@selector(method)      \
withMethod:@selector(newMethod) error:&err]) {         \
    NSLog(@"%@", err); return NO; \
}

#define ASSERTING_METHOD_CHECK(theClass, orMethod, altMethod, origImp, altImp, fatMsg)                         \
ASSERTING_METHOD_CHECK_WITH_SELECTOR(theClass, @selector(orMethod), @selector(altMethod), origImp, altImp, fatMsg);

#define ASSERTING_METHOD_CHECK_WITH_SELECTOR(theClass, orSelector, altSelector, origImp, altImp, fatMsg)                         \
if (!origImp) { \
    BOOL isClass = object_isClass(theClass); \
    fatMsg = [NSString stringWithFormat:@"original method %@ not found for class %@", NSStringFromSelector(orSelector), isClass ? theClass : [theClass class]]; \
    NSAssert(origImp != nil, fatMsg); \
} else if (!altImp) { \
    BOOL isClass = object_isClass(theClass); \
    fatMsg = [NSString stringWithFormat:@"alternate method %@ not found for class %@", NSStringFromSelector(altSelector), isClass ? theClass : [theClass class]]; \
    NSAssert(altImp != nil, fatMsg); \
}

#define ASSERTING_MULTI_CLASS_METHOD_CHECK(origClass, altClass, orSelector, altSelector, origImp, altImp, fatMsg)                         \
if (!origImp) { \
    BOOL isClass = object_isClass(origClass); \
    fatMsg = [NSString stringWithFormat:@"original method %@ not found for class %@", NSStringFromSelector(orSelector), isClass ? origClass : [origClass class]]; \
    NSAssert(origImp != nil, fatMsg); \
} else if (!altImp) { \
    BOOL isClass = object_isClass(altClass); \
    fatMsg = [NSString stringWithFormat:@"alternate method %@ not found for class %@", NSStringFromSelector(altSelector), isClass ? altClass : [altClass class]]; \
    NSAssert(altImp != nil, fatMsg); \
}

#define BOOL_METHOD_CHECK(theClass, orMethod, altMethod, origImp, altImp, errMsg)                         \
if (!origImp) { \
    errMsg = [NSString stringWithFormat:@"original method %@ not found for class %@", NSStringFromSelector(@selector(orMethod)), [theClass class]]; \
    NSLog(@"%@", errMsg); \
    return NO; \
} else if (!altImp) { \
    errMsg = [NSString stringWithFormat:@"alternate method %@ not found for class %@", NSStringFromSelector(@selector(altMethod)), [theClass class]]; \
    NSLog(@"%@", errMsg); \
    return NO; \
}

#define setErrorIfAvailable(error_, domain_, code_, userInfo_) \
if (error_) {   \
    *error_ = [NSError errorWithDomain:domain_ code:code_ userInfo:userInfo_]; \
}

@interface NSObject (MAPSwizzle)

+ (BOOL) performSwizzle;
+ (BOOL) performNSObjectSwizzle;

+ (instancetype) baseAllocWithZone:(NSZone *)zone;

/**
 * Replace the instance/class method for the provided selector with the provided
 * implementation.
 *
 * @note Unlike other swizzle methods, the implementation for the specified
 *   selector is overridden if present, otherwise it will be added. This means
 *   there is no new selector added to invoke the original implementation.
 *   Instead, the original implementation is returned and may be stored by the
 *   caller if they wish to invoke it.
 *
 * @param originalSelector the selector to replace the implementation of
 * @param replaceImp the IMP to set for the specified selector
 *
 * @returns the original implementation for the specified selector, if present.
 *   Otherwise, returns NULL.
 */
+ (IMP)replaceInstanceMethodSelector:(SEL)originalSelector withImp:(IMP)replaceImp;
+ (IMP)replaceClassMethodSelector:(SEL)originalSelector withImp:(IMP)replaceImp;

/**
 * Replace the instance/class method for the provided selector with the provided
 * block.
 *
 * @note Unlike other swizzle methods, the implementation for the specified
 *   selector is overridden if present, otherwise it will be added. This means
 *   there is no alternate selector by which to invoke the original implementation.
 *   Instead, the original implementation is returned and may be stored by the
 *   caller if they wish to invoke it.
 *
 * @param originalSelector the selector to replace the implementation of
 * @param block the block from which to acquire an IMP to set for the specified
 *   selector. Must actually be a block.
 *
 * @returns the original implementation for the specified selector, if present.
 *   Otherwise, returns NULL.
 */
+ (IMP)replaceInstanceMethodSelector:(SEL)originalSelector withBlock:(id)block;
+ (IMP)replaceClassMethodSelector:(SEL)originalSelector withBlock:(id)block;

/**
 *
 */
+ (IMP)replaceInstanceMethodSelector:(SEL)originalSelector withSelector:(SEL)replaceSelector;
+ (IMP)replaceClassMethodSelector:(SEL)originalSelector withSelector:(SEL)replaceSelector;

+ (IMP)replaceMethodSelector:(SEL)originalSelector ofClass:(Class)cls withImp:(IMP)replaceImp andMethod:(Method)originalMethod;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
+ (void) DumpObjcMethods:(Class)clz;
#pragma clang diagnostic pop
/**
 *
 */
@property(nonatomic, readonly) NSMutableDictionary *mstDict;

@end
