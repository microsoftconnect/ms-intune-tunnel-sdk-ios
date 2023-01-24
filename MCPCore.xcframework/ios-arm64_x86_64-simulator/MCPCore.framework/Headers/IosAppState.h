//
//  IosAppState.h
//  mstapnext_injectable_ios
//
//  Created by Sujan Kota on 11/2/16.
//  Copyright © 2016 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef IosAppState_h
#define IosAppState_h

#include "IPlatformAppState.h"

#pragma GCC visibility push(default)
class IosAppState: public IPlatformAppState {

public:
    IosAppState();
    virtual ~IosAppState() {};
    
    // IPlatformAppState
    virtual std::vector<std::string> getGroupedAppIds() override;
    virtual std::vector<std::string> getAppPaths(std::vector<std::string> integrityFiles) override;
    virtual std::vector<std::string> getPluginPaths() override;
    virtual std::vector<std::string> getCleanupAppPathsIfNeeded() override;
    virtual void notifyAppUnblocked() override;
};
#pragma GCC visibility pop

#endif /* IosAppState_h */
