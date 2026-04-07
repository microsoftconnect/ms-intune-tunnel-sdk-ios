//
//  MicrosoftTunnelDiagnosticsViewController.h
//  MicrosoftTunnelApi
//
//  Copyright © Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <MicrosoftTunnelApi/MicrosoftTunnelEnums.h>

NS_ASSUME_NONNULL_BEGIN

@class MicrosoftTunnelConfiguration;
@protocol MicrosoftTunnelDelegate;

/**
 * A view controller that displays diagnostic information for the Microsoft Tunnel SDK.
 * This includes connection status, tunnel configuration, split tunneling rules,
 * DNS configuration, and provides log collection capabilities.
 *
 * @discussion This view controller is provided by the SDK for integration into consumer apps.
 * It requires iOS 15.0 or later for full functionality.
 *
 * To keep the diagnostics view updated with real-time tunnel information, call the
 * updateTunnelConfiguration: method when the tunnel configuration changes (typically
 * in your MicrosoftTunnelDelegate's onTunnelConfigurationAvailable: callback).
 *
 * @code
 * MicrosoftTunnelDiagnosticsViewController *diagnostics = [[MicrosoftTunnelDiagnosticsViewController alloc] init];
 * [self presentViewController:diagnostics animated:YES completion:nil];
 * @endcode
 */
API_AVAILABLE(ios(15.0))
__attribute__ ((visibility ("default")))
@interface MicrosoftTunnelDiagnosticsViewController : UIViewController

/**
 * Updates the diagnostics view with current tunnel configuration information.
 * Call this method when tunnel configuration changes to ensure the displayed
 * information is accurate and up-to-date.
 *
 * @param config The current tunnel configuration object provided by the SDK
 */
- (void)updateTunnelConfiguration:(MicrosoftTunnelConfiguration *)config;

/**
 * Updates the diagnostics view with the current connection status.
 * Call this method when the connection status changes to update the UI.
 *
 * @param status The current Microsoft Tunnel connection status
 */
- (void)updateConnectionStatus:(MicrosoftTunnelStatus)status;

@end

NS_ASSUME_NONNULL_END
