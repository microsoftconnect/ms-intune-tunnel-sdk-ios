//
//  IMCPPluginLoaderService.h
//  MCPCommon
//
//  Created by Tim Champagne Jr on 2/28/22.
//  Copyright © 2022 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//
#ifndef IMCPPluginLoaderService_h
#define IMCPPluginLoaderService_h

#include "IMCPService.h"
#include "PluginLoader.h"

MCP_BEGIN_EXPORT()

class IMCPPluginLoaderService : public IMCPService,
                                public IPluginLoader
{
public:
    virtual ~IMCPPluginLoaderService() = default;

protected:
    IMCPPluginLoaderService() = default;
};

MCP_END_EXPORT()

#endif  // IMCPPluginLoaderService_h
