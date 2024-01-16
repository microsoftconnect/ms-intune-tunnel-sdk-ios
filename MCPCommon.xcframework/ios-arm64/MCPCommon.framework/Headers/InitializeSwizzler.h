//
//  InitializeSwizzler.h
//  MCPCommon
//
//  Created by Richard Perry on 4/19/23.
//  Licensed to Microsoft under Contract #7267038.
//

#import <Foundation/Foundation.h>

#import "MCP.h"

NS_ASSUME_NONNULL_BEGIN

/** @brief Handles swizzling of initialize to classes that need to be postponed until app control.
    @remark Registered classes are currently hardcoded in array _swizzledClasses
*/
MCP_EXPORT
@interface InitializeSwizzler : NSObject
/// Swizzles all registered classes to do nothing when initialize is called
+(BOOL) swizzleAllRegisteredClasses;
/// Puts original initialize function for all registered classes back
+(void) unswizzleAllRegisteredClasses;
/// Calls the original initialize function of all registered classes
+(void) callOriginalInitializeForAllRegisteredClasses;
@end

NS_ASSUME_NONNULL_END
