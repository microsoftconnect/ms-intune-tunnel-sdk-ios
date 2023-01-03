//
//  IosMCPServicesLoader.h
//  MCPCommon
//
//  Created by Tim Champagne Jr on 2/28/22.
//  Copyright © 2022 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//
#ifndef IosMCPServicesLoader_h
#define IosMCPServicesLoader_h

#include <utility>

#include "IMCPServices.h"
#include "MCPServicesLoaderBase.h"

MCP_BEGIN_EXPORT()

class IosMCPServicesLoader : public MCPServicesLoaderBase
{
public:
    IosMCPServicesLoader() = default;
    virtual ~IosMCPServicesLoader() = default;

protected:
    // PluginLoader virtual method overrides
    PluginLoader *createPluginLoader() override;
};

MCP_END_EXPORT()

#endif  // IosMCPServicesLoader_h
