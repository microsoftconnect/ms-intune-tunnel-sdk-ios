//
//  NSNotificationCenter+MAP_NSNotificationCenter.h
//  mstapnext_injectable_ios
//
//  Created by Vadim Lozko on 8/23/16.
//  Copyright © 2016 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#import <UIKit/UIKit.h>

__attribute__ ((visibility ("default")))
@interface MAP_NSAppNotificationCenter : NSNotificationCenter

+ (MAP_NSAppNotificationCenter *)appDefaultCenter;

- (void)postDeferredNotificationWithName:(NSNotificationName)aName;
- (void)receivedMstNotification:(NSNotification *)notification;

@end

@interface NSNotificationCenter (MAP_NSNotificationCenter)

+ (void)disableNotification:(NSNotificationName)name;
+ (void)enableNotification:(NSNotificationName)name;

/**
 * Doc stub: Swizzle methods automatically identified as create/init methods to
 * return a MAP replacement object for NSString
 */
+ (BOOL)performSwizzle;

/**
 * Binary-rewritten method to allow modification of application-level
 * notifications independent of system-level notifications. Blocking the latter
 * can have unintended consequences for certain classes of notifications.
 *
 * Note: this selector name is replaced during wrapping (in MachO.py) and cannot
 *   be changed without making modifications there. "mstDfltCenter" was chosen
 *   because it is the same number of bytes as the selector name that it is
 *   replacing, "defaultCenter", which means that we don't need to shift the
 *   entire application binary to accomodate a different length string.
 */
+ (MAP_NSAppNotificationCenter *)mstDfltCenter;

- (BOOL)isNotificationDisabled:(NSNotificationName)aName;

@end


@interface NSPointerArray (NewMethods)
- (void)addObject:(id)object;
- (BOOL)containsObject:(id)object;
- (void)removeAllNulls;
@end
