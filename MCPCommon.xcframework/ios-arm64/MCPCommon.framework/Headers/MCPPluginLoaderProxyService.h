//
//  MCPPluginLoaderService.h
//  MCPCommon
//
//  Created by Tim Champagne Jr on 2/28/22.
//  Copyright © 2022 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//
#ifndef MCPPluginLoaderService_h
#define MCPPluginLoaderService_h

#include "MCPServiceBase.h"
#include "IMCPPluginLoaderService.h"

MCP_BEGIN_EXPORT()

// Proxy-based service that avoids the PluginLoader needing concrete knowledge of MCP service types
class MCPPluginLoaderProxyService : public MCPServiceMixin<IMCPPluginLoaderService>
{
public:
    using base_type = MCPServiceMixin<IMCPPluginLoaderService>;

    MCPPluginLoaderProxyService(IMCPServices &services, IPluginLoader &pluginLoader);
    virtual ~MCPPluginLoaderProxyService() override = default;

    virtual ACSTATUS Init(IClientLock *pClientLock) override;
    virtual void RegisterObserver(IPluginObserver &observer) override;
    virtual void DeregisterObserver(IPluginObserver &observer) override;
    virtual ACSTATUS AssociatePlatformPlugin(IPlatformPlugin &platformPlugin) override;
    virtual ACSTATUS OpenAll(const std::vector<std::string> &pluginPaths) override;
    virtual ACSTATUS AutoLoadAll(IMCPServices *pMCPServices) override;
    virtual ACSTATUS LoadPlugin(const std::string &path, const std::string &pluginName,
                                IMCPServices *pMCPServices) override;

private:
    IPluginLoader &m_pluginLoader;
};

MCP_END_EXPORT()

#endif  // MCPPluginLoaderService_h
