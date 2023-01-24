//
//  MAPSwizzleClassMethod.h
//  mstapnext_injectable_ios
//
//  Created by Tim Champagne Jr. on 10/29/15.
//  Copyright © 2015 Mocana. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef MAPSwizzleClassMethod_h
#define MAPSwizzleClassMethod_h

/*------------------------------------------------------------------
 Utility class to perform swizzling on class methods (JRSwizzle
 does not seem to have been designed to replace any class method
 with another class method).
 ------------------------------------------------------------------*/
__attribute__ ((visibility ("default")))
@interface MAPSwizzleClassMethod : NSObject {}

+(BOOL) swizzleClassName:(NSString *) sourceName
                selector:(SEL) selector
               withClass:(NSString *) destName
             andSelector:(SEL) destSelector;

+ (BOOL) swizzleClass:(Class) source
             selector:(SEL) selector
            withClass:(Class) dest
          andSelector:(SEL) destSelector;

@end

#endif /* MAPSwizzleClassMethod_h */
