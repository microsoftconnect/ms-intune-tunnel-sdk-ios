//
//  IAppDelegateService.h
//  MCPCore
//
//  Created by Tim Champagne Jr on 4/27/22.
//  Licensed to Microsoft under Contract #7267038.  
//

#ifndef IAppDelegateService_h
#define IAppDelegateService_h

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "IMCPService.h"
#import "MCPUIApplicationDelegateLayer.h"
#import "CLIArgs.h"

#pragma GCC visibility push(default)

class IAppDelegateListener
{
public:
    virtual ~IAppDelegateListener() = default;

    virtual void OnInjectableUIApplicationMain() = 0;

protected:
    IAppDelegateListener() = default;
};

class IAppDelegateService : public IMCPService
{
public:
    virtual ~IAppDelegateService() override = default;

    virtual bool IsAppDelegateSetupComplete() = 0;
    virtual UIWindow *GetInitialAppDelegateWindow() = 0;

    virtual void RegisterAppDelegateListener(IAppDelegateListener &appDelegateListener) = 0;
    virtual IAppDelegateListener *GetAppDelegateListener() = 0;

    virtual void InstallDummyDelegate(id<UIApplicationDelegate> dummyDelegate) = 0;

    virtual UIViewController *GetPresentationViewController() = 0;

    virtual void AddApplicationDelegateLayer(id<MCPUIApplicationDelegateLayer> layer) = 0;

    virtual CLIArgs* getCLIArgs() = 0;
    virtual CFRunLoopRef GetRunLoop() = 0;
    
    virtual bool protectedDataAvailable() = 0;
    
    virtual void runBlockedBlockIfNeeded() = 0;
    
    virtual void sceneRunBlockIfNeeded() = 0;
    
    virtual void tryBackgroundFetch() = 0;
    
    virtual bool isSameAsService(id<UIApplicationDelegate> delegate) = 0;
    
    virtual void performBackgroundFetchWithDelegate(id<UIApplicationDelegate> delegate) = 0;
    
    virtual void performApplicationWillTerminate() = 0;
    
    virtual void backgroundFetchTimedOut() = 0;
    
    virtual void transitionApp() = 0;
    
    virtual pthread_key_t GetAppDelegateBypassKey() = 0;
    virtual pthread_key_t GetSceneDelegateBypassKey() = 0;


protected:
    IAppDelegateService() = default;
};

#pragma GCC visibility pop

#endif  // IAppDelegateService_h
