//
//  MCPCorePolicyBridge.h
//  MCPCore
//
//  Created by Richard Perry on 4/28/22.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef MCPCorePolicyBridge_hpp
#define MCPCorePolicyBridge_hpp

#include <stdio.h>
#include "MstapNextCoreManager.h"
#include "PluginLoader.h"
#include "PlatformNetworkReachabilityImpl.h"
#include "PlatformSecureClipboardProvider.h"
#include "IPlatformInterceptionProvider.h"
#include "PlatformWindowManager.h"
#include "IPlatformSecureWebStackManager.h"
#include "IMCPServicesLoader.h"
#include "IStorageLocationProvider.h"
#include "IPlatformCertificateProvider.h"
#include "IPlatformAppConfigProvider.h"
#include "PlatformLifecycleForwarderBase.h"
#include "MstapNextSecureDataProvider.h"


class MCPCorePolicyBridge : public IMstapNextCoreManagerCB,
                            public IPluginObserver
{
public:
    MCPCorePolicyBridge();
    virtual ~MCPCorePolicyBridge() override = default;
    virtual IMCPServicesLoader* GetMCPServicesLoader() override;
    virtual ACSTATUS SetupCoreManager();
    MstapNextCoreManager *GetMstapNextCoreManager()
    {
        return m_upMstapNextCoreManager.get();
    };
protected:
    virtual std::string getServiceKey() const = 0;
    virtual std::string loadPolicyFile(std::string fileName) = 0;
    virtual std::string makeLogDir() = 0;
    virtual ACSTATUS onPostStart(MstapNextCoreManager &mstapNextCoreManager) = 0;
    // strongly owned
    SmarterPtr<MstapNextCoreManager> m_upMstapNextCoreManager;
    PlatformNetworkReachabilityPtr m_upReachability;
    std::unique_ptr<MstapNextSecureDataProvider> m_upSecureDataProvider;
    std::unique_ptr<IPlatformSecureWebStackManager> m_upSWSManager;
    IAssetProvider *m_pAssetProvider;

    // Instances that must be available before the call to Create
    IMCPServices *m_pMCPServices;
    std::unique_ptr<IMCPServicesLoader> m_upMCPServicesLoader;
    std::unique_ptr<PlatformLifecycleForwarderBase> m_upLifecycleForwarder;
    std::unique_ptr<IDispatcher> m_upDispatcher;
    PlatformPerpReportImplPtr m_upPerpReport;
    std::unique_ptr<IPlatformWindowManager> m_upWindowManager;

    // Instances that must be available after the call to Register
    std::unique_ptr<PlatformWidgetFrameImpl> m_upWidgetFrame;
//    std::unique_ptr<IosWebViewFrame> m_upWebViewFrame;
    PlatformVpnStateHandlerImplPtr m_upVpnStateHandler;
    std::unique_ptr<IStorageLocationProvider> m_upStorageLocationProvider;
    std::unique_ptr<IPlatformAppState> m_upAppState;
    std::unique_ptr<IPlatformNotificationProvider> m_upNotificationProvider;
    std::unique_ptr<IPlatformCertificateProvider> m_upCertificateProvider;
    std::unique_ptr<IPlatformAppConfigProvider> m_upAppConfigProvider;
    SmarterPtr<IPlatformInterceptionProvider> m_upInterceptionProvider;
    std::string m_mapSubDir;
    std::string m_staticPolicyJson;
    std::string m_injectableVersionInfoJson;
    std::string m_certificatePolicyJson;
    std::string m_internalDatastoreSubDir;
    std::string m_logsDirPath;
    std::unique_ptr<MstapNextInterception> m_upMstapNextInterception;
};

#endif /* MCPCorePolicyBridge_hpp */
