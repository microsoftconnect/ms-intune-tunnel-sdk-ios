//
//  IUIService.h
//  mstapnext_injectable_ios
//
//  Created by Connor Kelley on 1/20/22.
//  Copyright © 2022 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef IUIService_h
#define IUIService_h

#include <cassert>

#include "IMCPService.h"
#include "UIImportance.h"
#include "UserMessage.h"
/**
 * Interface to a public core service for presenting UI
 *
 * @note locks are placed in the interface itself with the intent that there is
 *   no way to acquire an instance of this public service interface that is not
 *   threadsafe, in a way that is fairly transparent and readable for both
 *   consumers and implementers. The effectiveness of this attempt relies on
 *   your continued adherance to this pattern. Willful deviation will be met
 *   with an indecipherable mess of template code that is unavoidably thread
 *   safe.
 */

// Note: could move this somewhere common for re-use in checking service capabilities
#define USE_CAPABILITY_ASSERTS 1
#ifdef USE_CAPABILITY_ASSERTS
#define CAPABILITY_CHECK(pService, capability) assert(pService->IsSupported(capability))
#else
#define CAPABILITY_CHECK(pService, capability)
#endif
#define CAPABILITY_CHECK_THIS(capability) CAPABILITY_CHECK(this, capability)

class IPlatformUserInterfaceProvider;
class IWidgetActionHandler;

class IUIService : public IMCPService
{
public:
    using base_type = IMCPService;

    enum class CAPABILITY
    {
        WIDGET,
        ALERT,
        WEBVIEW,
        TOAST,
        PROVIDER,
        CUSTOMIZATION,
        BIOMETRIC
    };

    virtual ~IUIService() override = default;

    virtual bool IsSupported(const CAPABILITY capability) const final
    {
        ClientLockGuard lockGuard(GetMCPLock());

        return isSupported(capability);
    }

    virtual void PerformPlatformSetup() final
    {
        ClientLockGuard lockGuard(GetMCPLock());

        return performPlatformSetup();
    }

    virtual void *GetProviderImpl() final
    {
        ClientLockGuard lockGuard(GetMCPLock());

        CAPABILITY_CHECK_THIS(CAPABILITY::PROVIDER);
        
        return getProviderImpl();
    }
    
    virtual void ShowQueuedMessage() final
    {
        ClientLockGuard lockGuard(GetMCPLock());

        CAPABILITY_CHECK_THIS(CAPABILITY::TOAST);
        
        return showQueuedMessage();
    }

    virtual void LoadAppCustomization() final
    {
        ClientLockGuard lockGuard(GetMCPLock());

        CAPABILITY_CHECK_THIS(CAPABILITY::CUSTOMIZATION);
        
        return loadAppCustomization();
    }
    
    virtual void UpdateStatusLabel(const UserMessage &msg) final
    {
        ClientLockGuard lockGuard(GetMCPLock());

        CAPABILITY_CHECK_THIS(CAPABILITY::TOAST);
        
        return updateStatusLabel(msg);
    }

    virtual ACSTATUS ShowAlert(const UserMessage &title, const UserMessage &message, const UserMessage &confirmButton,
                               IWidgetActionHandler *pHandler, const UI_IMPORTANCE importance) final
    {
        ClientLockGuard lockGuard(GetMCPLock());

        CAPABILITY_CHECK_THIS(CAPABILITY::ALERT);

        return showAlert(title, message, confirmButton, pHandler, importance);
    }

protected:
    // virtual methods that MUST be overriden by implementers
    virtual bool isSupported(const CAPABILITY capability) const = 0;
    virtual void performPlatformSetup() = 0;
    virtual void showQueuedMessage() = 0;
    virtual void loadAppCustomization() = 0;
    virtual void updateStatusLabel(const UserMessage &msg) = 0;
    virtual void *getProviderImpl() = 0;
    virtual ACSTATUS showAlert(const UserMessage &title, const UserMessage &message, const UserMessage &confirmButton,
                               IWidgetActionHandler *pHandler, const UI_IMPORTANCE importance) = 0;
};

#endif /* IUIService_h */
