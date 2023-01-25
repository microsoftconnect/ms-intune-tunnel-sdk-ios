//
//  IPlatforUserInterfaceProvider.h
//
//
//  Created by Connor Kelley on 1/20/22.
//  Copyright © 2022 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef IPlatformUserInterfaceProvider_h
#define IPlatformUserInterfaceProvider_h

#include "UserMessage.h"
#include "IUIService.h"

#pragma GCC visibility push(default)

class IWindowService;

class IPlatformUserInterfaceProvider : public IMCPComponent
{
public:
    virtual ~IPlatformUserInterfaceProvider() = default;

    virtual bool IsSupported(const IUIService::CAPABILITY capability) const = 0;
    virtual void PerformPlatformSetup() = 0;
    virtual void ShowQueuedMessage() = 0;
    virtual void LoadAppCustomization() = 0;
    virtual void UpdateStatusLabel(const UserMessage &msg) = 0;
    virtual void *GetProviderImpl() = 0;
    virtual ACSTATUS ShowAlert(const UserMessage &title, const UserMessage &message, const UserMessage &confirmButton,
                               IWidgetActionHandler *pHandler, const UI_IMPORTANCE importance) = 0;
    
protected:
    IPlatformUserInterfaceProvider() = default;
    
private:
    IPlatformUserInterfaceProvider &operator=(const IPlatformUserInterfaceProvider &) = delete;
    IPlatformUserInterfaceProvider(const IPlatformUserInterfaceProvider &) = delete;
    IPlatformUserInterfaceProvider(IPlatformUserInterfaceProvider &&) = delete;
};


#pragma GCC visibility pop

#endif // IPlatformUserInterfaceProvider_h
