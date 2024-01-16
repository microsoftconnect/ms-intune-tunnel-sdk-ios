//
//  MCPUIApplicationDelegateLayer.h
//  MCPCore
//
//  Created by Tim Champagne Jr on 5/2/22.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef MCPUIApplicationDelegateLayer_h
#define MCPUIApplicationDelegateLayer_h

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#pragma GCC visibility push(default)

// A loosely-defined protocol to allow plugins to influence how the core
// injectable handles UIApplicationDelegate-related stuff. In the interest of
// not over-engineering or being overly speculative, this is fairly simple for
// now but it may evolve over time.
@protocol MCPUIApplicationDelegateLayer

@property (nonatomic, weak) id<MCPUIApplicationDelegateLayer> nextLayer;

-(BOOL)actualAppDelegate:(id<UIApplicationDelegate>)delegate application:(UIApplication *)application willFinishLaunchingWithOptions:(nullable NSDictionary<UIApplicationLaunchOptionsKey, id> *)launchOptions;
-(BOOL)actualAppDelegate:(id<UIApplicationDelegate>)delegate application:(UIApplication *)application didFinishLaunchingWithOptions:(nullable NSDictionary<UIApplicationLaunchOptionsKey, id> *)launchOptions;
-(void)actualAppDelegate:(id<UIApplicationDelegate>)delegate applicationDidFinishLaunching:(UIApplication *)application;

- (void)installInitialAppDelegate:(id<UIApplicationDelegate>)newDelegate;
- (BOOL)swapMCPSwizzleDelegate:(id<UIApplicationDelegate>)newDelegate;

- (UIWindow *)UIWindowFromAlloc:(UIWindow *)windowFromAlloc initWithFrame:(CGRect)frame;
- (UIWindow *)UIWindowFromAlloc:(UIWindow *)windowFromAlloc initWithCoder:(NSCoder *)aDecoder;

- (int)invokeOriginalEntryPointWithArgc:(int)argc argv:(char *[])argv;

@end

#pragma GCC visibility pop

#endif  // MCPUIApplicationDelegateLayer_h

