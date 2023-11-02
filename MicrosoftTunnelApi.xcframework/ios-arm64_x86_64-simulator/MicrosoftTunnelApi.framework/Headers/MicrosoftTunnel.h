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

__attribute__ ((visibility ("default")))
@interface MicrosoftTunnelSplitConfiguration : NSObject
@property(readonly, strong) NSString* _Nonnull ipAddress;
@property(readonly) unsigned int prefix;
@end

__attribute__ ((visibility ("default")))
@interface MicrosoftTunnelConfiguration : NSObject
@property(readonly, strong) NSString* _Nonnull remoteIpAddress;

@property(readonly, strong) NSString* _Nonnull tunnelIpAddress;
@property(readonly, strong) NSString* _Nonnull tunnelNetmask;

@property(readonly) unsigned int mtu;
@property(readonly, strong) NSArray<NSString*>* _Nonnull dnsServers;
@property(readonly, strong) NSString* _Nonnull dnsDomain;
@property(readonly, strong) NSArray<NSString*>* _Nonnull dnsSearchEntries;

@property(readonly, strong) NSArray<MicrosoftTunnelSplitConfiguration*>* _Nonnull splitConfigurationIncludeEntries;
@property(readonly, strong) NSArray<MicrosoftTunnelSplitConfiguration*>* _Nonnull splitConfigurationExcludeEntries;
@property(readonly) bool splitTunnelingEnabled;

@end

/**
 * Callback interface for receiving API status events, notifications and errors.
 * To register for callbacks use {@link MicrosoftTunnel#registerDelegate:} or
 * {@link MicrosoftTunnel#initWithDelegate:logDelegate:config:}
 */
@protocol MicrosoftTunnelDelegate <NSObject>

/**
 * Callback indicating the various events in a single method.
 */
- (void)onReceivedEvent:(MicrosoftTunnelStatus)event;

/**
 * Callback indicating the API has successfully been initialized.
 * Expected after invoking {@link MicrosoftTunnel#init:} or one of its variants.
 */
- (void)onInitialized;

/**
 * Callback indicating the VPN session was successfully established.
 * Expected after invoking {@link MicrosoftTunnel#connect()}.
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
 * Expected after invoking {@link MicrosoftTunnel#disconnect()}.
 */
- (void)onDisconnected;

/**
 * Callback indicating an error has ben encountered.
 */
- (void)onError:(MicrosoftTunnelError)error;


@optional
/**
 * Callback indicating an oauth token is needed.
 */
- (void)onTokenRequiredWithCallback:(TokenRequestCallback _Nonnull) tokenCallback withFailedToken:(NSString* _Nonnull) failedToken;

/**
 * Callback to get the view controller to present interactive MSAL login
 */
- (UIViewController* _Nonnull)onPresentationViewControllerRequired;

/**
 * Callback when the tunnel configuration is available from the connection
 */
- (void)onTunnelConfigurationAvailable:(MicrosoftTunnelConfiguration* _Nonnull) config;
@end

/**
 * Delgate for receiving API log messages.
 * To register for callbacks use {@link MicrosoftTunnel#registerLogDelegate:}
 * or pass a MobileAccessLogListener to
 * {@link MicrosoftTunnel#initWithDelegate:logDelegate:config:}
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
@interface MicrosoftTunnel : NSObject

@property(class, nonatomic, readonly, strong) MicrosoftTunnel* _Nonnull sharedInstance;
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
 * @return An API error {@link MicrosoftTunnelError}
 */
- (MicrosoftTunnelError)microsoftTunnelInitialize;

/**
 * Deinitializes Microsoft Tunnel API infrastructure.
 */
- (void)microsoftTunnelDeinitialize;

/**
 * Initializes Microsoft Tunnel API infrastructure.
 *
 * @param delegate Delegate for events {@link MicrosoftTunnelDelegate}
 * @param configDictionary Configuration items used to determine what is to be logged, intercepted, and values for Tunnel connection to be established
 * @return An API error {@link MicrosoftTunnelError}
 */
- (MicrosoftTunnelError)microsoftTunnelInitializeWithDelegate:(nonnull id<MicrosoftTunnelDelegate>)delegate config:(nonnull NSDictionary <NSString *, NSString*>*)config;

/**
 * Initializes Microsoft Tunnel API infrastructure.
 *
 * @param delegate Delegate for events {@link MicrosoftTunnelDelegate}
 * @param logDelegate Delegate for logs {@link MicrosoftTunnelLogDelegate}
 * @param configDictionary Configuration items used to determine what is to be logged, intercepted, and values for Tunnel connection to be established
 * @return The initialized instance, or nil on an error
 */
- (MicrosoftTunnelError)microsoftTunnelInitializeWithDelegate:(nonnull id<MicrosoftTunnelDelegate>)delegate logDelegate:(nonnull id<MicrosoftTunnelLogDelegate>)logDelegate config:(nonnull NSDictionary <NSString *, NSString*>*)config;

/**
 * Set configuration values. See {@link MicrosoftTunnelEnums.h} for configuration keys and values.
 *
 * @param configDictionary Configuration items used to determine what is to be logged, intercepted, and values for Tunnel connection to be established
 * @return An API error {@link MicrosoftTunnelError}
 */
- (MicrosoftTunnelError)setConfig:(nonnull NSDictionary <NSString *, NSString*>*)configDictionary;

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
 * Unregister a log delegate.
 */
- (void)unregisterLogDelegate;

/**
 * Initiate establishment of the VPN session and enables interception.
 *
 * @return An API error {@link MicrosoftTunnelError}
 */
- (MicrosoftTunnelError)connect;
/**
 * Disconnect an active VPN session and disables interception.
 *
 * @return An API error
 */
- (MicrosoftTunnelError)disconnect;
/**
 * Get the current API status.
 *
 * @return The API status {@link MicrosoftTunnelStatus}
 */
- (MicrosoftTunnelStatus)getStatus;

/**
 * Get the current API status as a string
 *
 * @return The API status {@link MicrosoftTunnelStatus} as a string
 */
- (NSString * _Nonnull)getStatusString;

/**
 * Get the MicrosoftTunnel version string.
 * @return The MobieAccessAPI versionString
 */
- (NSString * _Nonnull)getVersionString;

/**
 * Launches enrollment for MAM enrollment
 */
- (BOOL)launchEnrollment;

/**
 * Launches enrollment for MAM enrollment
 * 
 * @param doWipe If YES, selectively wipe the user's corporate data
 */
- (BOOL)launchUnenrollment:(BOOL)doWipe;

/**
 * Proxy handling of MSAL response to push to MSAL library
 */
- (BOOL)handleMSALResponse:(nonnull NSURL *)response sourceApplication:(nullable NSString *)sourceApplication;

@end
#pragma GCC visibility pop
