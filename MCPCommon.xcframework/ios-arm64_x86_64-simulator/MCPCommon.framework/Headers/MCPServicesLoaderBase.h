//
//  MCPServicesLoaderBase.h
//  MCPCommon
//
//  Created by Tim Champagne Jr on 2/28/22.
//  Copyright © 2022 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//
#ifndef MCPServicesLoaderBase_h
#define MCPServicesLoaderBase_h

#include <utility>

#include "IMCPServices.h"
#include "IMCPServicesLoader.h"

MCP_BEGIN_EXPORT()

// Note: this does not need to be a singleton, but the underlying PluginLoader is accessed as one today.
class MCPServicesLoaderBase : public IMCPServicesLoader
{
public:
    virtual ~MCPServicesLoaderBase() = default;

    IMCPServices *GetWeakMCPServices() override;

    // SWIG doesn't deal well with returning smart pointers
#ifndef SWIG
    SmarterPtr<IMCPServices> ReleaseMCPServices() override;

    bool InitAndAutoLoadServices(const std::vector<std::string> &pluginPaths,
                                 IPluginObserver *pPluginObserver = nullptr) override;

    SmarterPtr<IMCPPluginLoaderService>
    InitAndOpenPluginsForServices(const std::vector<std::string> &pluginPaths,
                                  IPluginObserver *pPluginObserver = nullptr) override;
#endif

protected:
    MCPServicesLoaderBase();
    MCPServicesLoaderBase(IMCPServices &preExistingMCPServices, const bool owned);
    MCPServicesLoaderBase(SmarterPtr<IMCPServices> upPreExistingMCPServices);

    virtual PluginLoader *createPluginLoader() = 0;

    SmarterPtr<IMCPServices> m_upMCPServices;
};

MCP_END_EXPORT()

#endif  // MCPServicesLoaderBase_h
