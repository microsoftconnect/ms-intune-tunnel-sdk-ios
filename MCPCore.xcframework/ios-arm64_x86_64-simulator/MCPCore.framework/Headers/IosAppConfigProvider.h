//
//  IosAppConfigProvider.h
//  mstapnext_injectable_ios
//
//  Created by Paul Tillotson 6/6/19.
//  Copyright © 2019 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef IosAppConfigProvider_h
#define IosAppConfigProvider_h

#include "atlas_client_types.h"
#include "IPlatformAppConfigProvider.h"

#pragma GCC visibility push(default)
class IosAppConfigProvider : public IPlatformAppConfigProvider
{
public:
    IosAppConfigProvider() = default;
    virtual ~IosAppConfigProvider() override = default;

    virtual ACSTATUS ApplyAppConfig(const std::string &appConfigContents) override;
    ACSTATUS ApplyAppConfig(NSDictionary *appConfigDict);
};
#pragma GCC visibility pop

#endif /* IosAppConfigProvider_h */
