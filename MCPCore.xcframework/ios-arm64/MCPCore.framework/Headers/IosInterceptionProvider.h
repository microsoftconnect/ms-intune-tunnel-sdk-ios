//
//  IosInterceptionProvider.h
//  MCPPluginSecurityPolicies
//
//  Created by Tim Champagne Jr. on 8/28/18.
//  Copyright © 2018 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef IosInterceptionProvider_h
#define IosInterceptionProvider_h

#include <string>
#import "IPlatformInterceptionProvider.h"
#import "SwiftSupportProviderPlugin.h"

#pragma GCC visibility push(default)
class IosInterceptionProvider : public IPlatformInterceptionProvider
{
public:
    IosInterceptionProvider();
    virtual ~IosInterceptionProvider() override = default;

    // trying to reconcile this with refactor changes.
    //   Re-enable these in the future.
#if 0
    virtual const std::vector<std::string> &GetInitialBlacklist() const override;
    virtual const std::vector<std::string> &GetInitialWhitelist() const override;

    virtual const std::string &GetSandboxLocation() override;
    virtual const std::string &GetSdcardLocation() override;

    virtual const bool IsSqliteLiteInterceptionSupported() const override;
#endif

    virtual ACSTATUS InitializePlatformInterception(IMstapNextCoreServices *pMstapNextCoreServices) override;
    
    virtual ACSTATUS InitializePlatformIOInterception(IMstapNextCoreServices *pMstapNextCoreServices) override;

    virtual ACSTATUS PluginPrepForAppTransition() override;
    virtual MBSTATUS performDeferredInit(const std::string &imageName) override;
    
    virtual void earlyBlacklistInitialization(MstapNextInterception *pMstapNextCoreServices) override;

private:
    std::string m_sandboxLocation;
    const std::string m_empty;
    SmarterPtr<SwiftSupportProvider> m_swiftSupportProvider;
};
#pragma GCC visibility pop

#endif /* IosInterceptionProvider_h */
