//
//  IosSecureWebStackManager.h
//  mstapnext_injectable_ios
//
//  Created by Tim Champagne Jr. on 6/21/17.
//  Copyright © 2017 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef IosSecureWebStackManager_h
#define IosSecureWebStackManager_h

#include "IPlatformSecureWebStackManager.h"
#include "WKWebViewBridge.h"

// This needs to be an NSObject today because we signal it with NSNotifications,
// but it's not entirely clear 1) why we need to do that, 2) what this is doing
// in the first place, or 3) why we need it, so leave it as-is for now.
@interface SWSAuthChallengeHandler : NSObject

@end

#pragma GCC visibility push(default)
class IosSecureWebStackManager : public IPlatformSecureWebStackManager
{
public:
    IosSecureWebStackManager();
    virtual ~IosSecureWebStackManager() override = default;

    virtual bool IsSupported() override;
    virtual bool ShouldInterceptCookies() override;
    virtual bool ShouldInterceptNetworkTraffic() override;
    virtual void SetInterceptWKWebView(bool shouldInterceptNetwork,
                                       bool shouldInterceptPersistence) override;
    virtual ACSTATUS PlatformWebStackSetupSync() override;
    virtual ACSTATUS PlatformInterceptionSetupSync() override;
    virtual ACSTATUS onAppTransition() override;
    virtual BasicWebStackRequest *createBasicWebStackRequest(IBasicWebStackRequestListener& listener,
                                                             IDispatcher &dispatcher,
                                                             const std::string &url,
                                                             const bool bypassPave = false) override;

    virtual void SetSecureWebStackService(ISecureWebStackServiceBase *pSWSService) override;
    
    virtual void DisableInterception() override;
    
    virtual void EnableInterception() override;
    
    virtual void ClearConnectionCache() override;
    
    virtual ACSTATUS ShouldInterceptWebView() override;

    virtual void OnSecureWebStackPolicyChanged() override;
    
private:
    SWSAuthChallengeHandler *m_pAuthChallengeHandler;
    WKWebViewBridge *m_pBridge;
    ISecureWebStackServiceBase *m_pSWSService;
    bool m_shouldInterceptWebview;
};
#pragma GCC visibility pop

#endif /* IosSecureWebStackManager_h */
