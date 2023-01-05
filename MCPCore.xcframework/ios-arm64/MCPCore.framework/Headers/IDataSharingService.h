//
//  IDataSharingService.h
//  mstapnext_injectable_ios
//
//  Created by Tiim Champagne Jr. on 4/29/22.
//  Copyright © 2022 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef IDataSharingService_h
#define IDataSharingService_h

#include "IMCPService.h"

class IDataSharingService : public IMCPService
{
public:
    virtual ~IDataSharingService() override = default;

    virtual ACSTATUS TryShowPrivacyScreen() final
    {
        ClientLockGuard lockGuard(GetMCPLock());

        return tryShowPrivacyScreen();
    }

protected:
    IDataSharingService() = default;

    // virtual methods that MUST be overriden by implementers
    virtual ACSTATUS tryShowPrivacyScreen() = 0;
};

#endif /* IDataSharingService_h */
