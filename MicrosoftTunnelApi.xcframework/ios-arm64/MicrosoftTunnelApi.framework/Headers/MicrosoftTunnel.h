//
//  MicrosoftTunnel.h
//  MobileAccess
//
//  Copyright © 2021 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//
#import <Foundation/Foundation.h>
#import <MicrosoftTunnelApi/MicrosoftTunnelEnums.h>
#import <UIKit/UIKit.h>

#pragma GCC visibility push(default)
typedef void (^TokenRequestCallback)(NSString* _Nonnull accessToken);

/**
 * Callback interface for receiving API status events, notifications and errors.
 * To register for callbacks use {@link MicrosoftTunnelAPI#registerDelegate:} or
 * {@link MicrosoftTunnelAPI#initWithDelegate:logDelegate:config:}
 */
@protocol MicrosoftTunnelDelegate <NSObject>

/**
 * Callback indicating the various events in a single method.
 */
- (void)onReceivedEvent:(MobileAccessStatus)event;

/**
 * Callback indicating the API has successfully been initialized.
 * Expected after invoking {@link MicrosoftTunnelAPI#init:} or one of its variants.
 */
- (void)onInitialized;

/**
 * Callback indicating the VPN session was successfully established.
 * Expected after invoking {@link MicrosoftTunnelAPI#connect()}.
 */
- (void)onConnected;

/**
 * Callback indicating VPN is in the process or re-establishing VPN.  Data communications may
 * temporarily be disrupted.
 */
- (void)onReconnecting;

/**
 * Callback indicating user interaction is required.
 */
- (void)onUserInteractionRequired;

/**
 * Callback indicating VPN has disconnected.
 * Expected after invoking {@link MicrosoftTunnelAPI#disconnect()}.
 */
- (void)onDisconnected;

/**
 * Callback indicating an error has ben encountered.
 */
- (void)onError:(MobileAccessError)error;


@optional
/**
 * Callback indicating an oauth token is needed.
 */
- (void)onTokenRequiredWithCallback:(TokenRequestCallback _Nonnull) tokenCallback withFailedToken:(NSString* _Nonnull) failedToken;

/**
 * Callback to get the view controller to present interactive MSAL login
 */
- (UIViewController* _Nonnull)onPresentationViewControllerRequired;

@end

/**
 * Delgate for receiving API log messages.
 * To register for callbacks use {@link MicrosoftTunnelAPI#registerLogDelegate:}
 * or pass a MobileAccessLogListener to
 * {@link MicrosoftTunnelAPI#initWithDelegate:logDelegate:config:}
 */
@protocol MicrosoftTunnelLogDelegate <NSObject>

/**
 * Callback when API is logging a message.
 */
- (void)logMessage:(unsigned)level
          logClass:(unsigned)logClass
             pTime:(nonnull const char*)pTime
            pLevel:(nonnull const char*)pLevel
       pClassLabel:(nonnull const char*)pClassLabel
              pLog:(nonnull const char*)pLog;

@end

/**
 * This class provides access to Mobile Access for configuration, controlling VPN connectivity, and
 * registering for API callbacks.
 */
__attribute__ ((visibility ("default")))
@interface MicrosoftTunnelAPI : NSObject

@property(class, nonatomic, readonly, strong) MicrosoftTunnelAPI* _Nonnull sharedInstance;

@property(nonatomic, assign)id<MicrosoftTunnelDelegate> _Nonnull delegate;
@property(nonatomic, assign)id<MicrosoftTunnelLogDelegate> _Nullable logDelegate;

/**
 * The Microsoft Tunnel API should not be instantiated directly. Use the {@link sharedInstance} property.
 */
- (instancetype _Nonnull)init NS_UNAVAILABLE;
+ (instancetype _Nonnull)new NS_UNAVAILABLE;

/**
 * Initializes Microsoft Tunnel API infrastructure.
 *
 * @return An API error {@link MobileAccessError}
 */
- (MobileAccessError)mobileAccessInitialize;

/**
 * Initializes Microsoft Tunnel API infrastructure.
 *
 * @param delegate Delegate for events {@link MicrosoftTunnelDelegate}
 * @param configDictionary Configuration items used to determine what is to be logged, intercepted, and values for Tunnel connection to be established
 * @return An API error {@link MobileAccessError}
 */
- (MobileAccessError)mobileAccessInitializeWithDelegate:(nonnull id<MicrosoftTunnelDelegate>)delegate config:(nonnull NSDictionary <NSString *, NSString*>*)config;

/**
 * Initializes Microsoft Tunnel API infrastructure.
 *
 * @param delegate Delegate for events {@link MicrosoftTunnelDelegate}
 * @param logDelegate Delegate for logs {@link MicrosoftTunnelLogDelegate}
 * @param configDictionary Configuration items used to determine what is to be logged, intercepted, and values for Tunnel connection to be established
 * @return The initialized instance, or nil on an error
 */
- (MobileAccessError)mobileAccessInitializeWithDelegate:(nonnull id<MicrosoftTunnelDelegate>)delegate logDelegate:(nonnull id<MicrosoftTunnelLogDelegate>)logDelegate config:(nonnull NSDictionary <NSString *, NSString*>*)config;

/**
 * Set configuration values. See {@link MicrosoftTunnelEnums.h} for configuration keys and values.
 *
 * @param configDictionary Configuration items used to determine what is to be logged, intercepted, and values for Tunnel connection to be established
 * @return An API error {@link MobileAccessError}
 */
- (MobileAccessError)setConfig:(nonnull NSDictionary <NSString *, NSString*>*)configDictionary;

/**
 * Register the API status listener.
 *
 * <p class="note"><b>Note:</b> This should be set prior to initialization in order to receive all state updates.
 * <p class="note"><b>Note:</b> There can be only one listener registered at a time.
 *
 * @param delegate Listener for events {@link MicrosoftTunnelDelegate}
 */
- (void)registerDelegate:(nonnull id<MicrosoftTunnelDelegate>)delegate;

/**
 * Register a class to receive log messages.
 *
 * @param logDelegate Log Class that implements the {@link MicrosoftTunnelLogDelegate} protocol.
 */
- (void)registerLogDelegate:(nonnull id<MicrosoftTunnelLogDelegate>)logDelegate;

/**
 * Initiate establishment of the VPN session and enables interception.
 *
 * @return An API error {@link MobileAccessError}
 */
- (MobileAccessError)connect;
/**
 * Disconnect an active VPN session and disables interception.
 *
 * @return An API error
 */
- (MobileAccessError)disconnect;
/**
 * Get the current API status.
 *
 * @return The API status {@link MobileAccessStatus}
 */
- (MobileAccessStatus)getStatus;

/**
 * Get the current API status as a string
 *
 * @return The API status {@link MobileAccessStatus} as a string
 */
- (NSString * _Nonnull)getStatusString;

/**
 * Get the MicrosoftTunnelAPI version string.
 * @return The MobieAccessAPI versionString
 */
- (NSString * _Nonnull)getVersionString;

/**
 * Launches enrollment for MAM enrollment
 */
- (BOOL)launchEnrollment;

/**
 * Proxy handling of MSAL response to push to MSAL library
 */
- (BOOL)handleMSALResponse:(nonnull NSURL *)response sourceApplication:(nullable NSString *)sourceApplication;

@end

#pragma GCC visibility pop
