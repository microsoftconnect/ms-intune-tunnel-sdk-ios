//
//  MicrosoftTunnelEnums.h
//  MobileAccess
//
//  Copyright © 2021 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//
#ifndef MICROSOFT_TUNNEL_ENUMS_H_
#define MICROSOFT_TUNNEL_ENUMS_H_

#pragma GCC visibility push(default)

/* Note: These enums may be mapped to a public API enum (ex. Java).
 *       Be sure to keep public instances in sync with the internal versions.
 */

/**
 * Status values used by the API that indicate the current status.  Often there are status values
 * indicating a transition but may also indicate and error occurred or user input is needed.
 * These values are reported by {@link MicrosoftTunnelDelegate#onReceivedEvent:} and
 * by invoking {@link MicrosoftTunnelAPI#getStatus}.
 */
typedef enum MobileAccessStatus {
    /**
     * The API has not yet been Initialized. The API must be initialized prior
     * to invoking methods besides {@link MicrosoftTunnelAPI#init}} and
     * {@link MicrosoftTunnelAPI#registerDelegate:}.
     */
    Uninitialized = 0,
    /**
     * The API has been initialized and is ready to accept {@link MicrosoftTunnelAPI#connect} calls.
     */
    Initialized,
    /**
     * The VPN session has completed establishment and is actively securing traffic.
     */
    Connected,
    /**
     * The VPN session has been disconnected (user initiated or other failure)
     * and is ready to accept {@link MicrosoftTunnelAPI#connect} calls.
     */
    Disconnected,
    /**
     * The VPN session is currently re-establishing.  Data communications may temporarily be
     * disrupted.
     */
    Reconnecting,
    /**
     * The API encountered a situation where user interaction is required.
     */
    UserInteractionRequired,
    /**
     * An error was encountered.
     */
    ErrorEncountered
} MobileAccessStatus;

/**
 * Error values used by the Microsoft Tunnel API.
 * The returned when invoking methods in {@link MicrosoftTunnelAPI} as well as by the callback method
 * {@link MicrosoftTunnelDelegate#onReceivedEvent:}.
 */
typedef enum MobileAccessError {
    /**
     * No error has occurred.
     */
    NoError = 0,
    /**
     * A necessary component or callback has not been implemented.
     */
    Unimplemented,
    /**
     * A timeout has occurred.
     */
    Timeout,
    /**
     * The configuration supplied was not valid.
     */
    InvalidConfig,
    /**
     * An error occurred but the reason was of unknown origins.
     */
    Unknown,
    /**
     * An unexpected error occurred.
     */
    UnexpectedError
} MobileAccessError;

/**
 * Config dictionary keys and values
 */
// @{

/**
 * Values used to configure the logging severity for individual log classes. To set log severity,
 * pass a config dictionary to {@link MicrosoftTunnelAPI#setConfig(Map)} or
 * {@link MicrosoftTunnelAPI#initialize(Application, MobileAccessListener, Map)} that includes that
 * includes the log class as a key and the severity as a value for each desired log class.
 */
// @{

// Interception Log Config keys
static const char *kLoggingClassInternal = "Internal";
static const char *kLoggingClassConnect = "Connect";
static const char *kLoggingClassPacket = "Packet";
static const char *kLoggingClassSocket = "Socket";
static const char *kLoggingClassHttp = "HTTP";
static const char *kLoggingClassIntune = "Intune";
static const char *kLoggingClassMobileAccess = "MobileAccess";

// Interception Log Config Values
static const char *kLoggingSeverityDebug = "debug";
static const char *kLoggingSeverityInfo  = "info";
static const char *kLoggingSeverityWarn  = "warn";
static const char *kLoggingSeverityMinor = "minor";
static const char *kLoggingSeverityMajor = "major";
static const char *kLoggingSeverityCrit  = "crit";

// Connection Config keys
static const char *kConnectionName = "com.microsoft.tunnel.connection_name";
static const char *kConnectionType = "com.microsoft.tunnel.connection_type";
static const char *kServerAddress  = "com.microsoft.tunnel.server_address";
static const char *kProxyAddress   = "com.microsoft.tunnel.proxy_address";
static const char *kProxyPort      = "com.microsoft.tunnel.proxy_port";
static const char *kPacUrl         = "com.microsoft.tunnel.proxy_pacurl";
static const char *kTrustedCertificates = "com.microsoft.tunnel.trusted_root_certificates";


// @}

// @}

#pragma GCC visibility pop

#endif // MICROSOFT_TUNNEL_ENUMS_H_
