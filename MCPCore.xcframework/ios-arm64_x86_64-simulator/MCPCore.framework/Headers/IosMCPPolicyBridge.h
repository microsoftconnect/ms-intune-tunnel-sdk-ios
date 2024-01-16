//
//  IosMCPPolicyBridge.h
//  MCPCore
//
//  Created by Richard Perry on 5/4/22.
//  Licensed to Microsoft under Contract #7267038.  
//

#import <Foundation/Foundation.h>
#import "MCPCorePolicyBridge.h"

class IosMCPPolicyBridge : public MCPCorePolicyBridge
{
public:
    IosMCPPolicyBridge();
    IosMCPPolicyBridge(NSBundle *appBundle);
    void SetSDKBundle(NSBundle *sdkBundle);
    void SetPluginPaths(std::vector<std::string>pluginPaths);
    NSString *getPathForResource(const std::string &resource, NSString *type);
protected:
    virtual std::string getServiceKey() const override;
    virtual std::string loadPolicyFile(std::string fileName) override;
    virtual std::string makeLogDir() override;
    virtual IPluginObserver *GetPluginObserver() override;
    virtual ACSTATUS onPostStart(MstapNextCoreManager &mstapNextCoreManager) override;
    virtual ACSTATUS OnPluginLoaderInitialized() override;
    virtual ACSTATUS OnCoreManagerCreated(MstapNextCoreManager &mstapNextCoreManager) override;
    virtual ACSTATUS OnCoreManagerInitialized(MstapNextCoreManager &mstapNextCoreManager) override;
    virtual ACSTATUS OnDeliveredInitialPolicy(MstapNextCoreManager &mstapNextCoreManager) override;
    
    virtual IPlatformLifecycleForwarder *GetLifecycleForwarder() override;
    virtual IDispatcher *GetDispatcher() override;
    virtual IAssetProvider *GetAssetProvider() override;
    virtual PlatformPerpReportImpl *GetPerpReport() override;
    virtual std::vector<std::string> GetPluginPaths() override;
    
    virtual PlatformWidgetFrameImpl *GetWidgetFrame() override;
    virtual PlatformWebViewFrame *GetWebViewFrame() override;
    virtual PlatformVpnStateHandlerImplPtr &GetVpnStateHandler() override;
    virtual IStorageLocationProvider *GetStorageLocationProvider() override;
    virtual IPlatformAppState *GetAppState() override;
    virtual IPlatformNotificationProvider *GetNotificationProvider() override;
    virtual IPlatformCertificateProvider *GetCertificateProvider() override;
    virtual IPlatformAppConfigProvider *GetAppConfigProvider() override;
    virtual const std::string &GetMapSubDir() override;
    virtual const std::string &GetStaticPolicyJson() override;
    virtual const std::string &GetInjectableVersionInfoJson() override;
    virtual const std::string &GetCertificatePolicyJson() override;
    virtual const std::string &GetInternalDatastoreSubDir() override;
    virtual const std::string &GetLogsDirPath() override;
    virtual MstapNextInterception *GetMstapNextInterception() override;
    
    virtual ACSTATUS AddPolicyGates(MstapNextCoreManager &mstapNextCoreManager) override;
    virtual std::string GetLicenseJson(MstapNextCoreManager &mstapNextCoreManager) override;
    
    virtual void OnOpeningPlugin(const std::string &libraryName) override;
private:
    NSBundle *m_pAppBundle;
    NSBundle *m_pSdkBundle;
    std::vector<std::string> m_pPluginPaths;
};

__attribute__ ((visibility ("default")))
@interface IosMCPBridge : NSObject
- (instancetype)initWithAppBundle:(NSBundle *)appBundle;
- (void)startSDK:(NSBundle *)sdkBundle;
- (void)setPluginPaths:(std::vector<std::string>)pluginPaths;
@end