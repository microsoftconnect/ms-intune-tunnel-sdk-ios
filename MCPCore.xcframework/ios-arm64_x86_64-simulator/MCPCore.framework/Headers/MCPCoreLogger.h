//
//  MCPCoreLogger.h
//  MCPCommon
//
//  Created by Tim Champagne Jr on 4/27/22.
//  Copyright © 2022 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef MCPCoreLogger_h
#define MCPCoreLogger_h

#include "DynamicLogger.h"
#include "MCP.h"

MCP_BEGIN_EXPORT()

extern const char kLogClassMCPCore[];

extern template struct LogDyn<kLogClassMCPCore>;
using LogMCPCore = LogDyn<kLogClassMCPCore>;

MCP_END_EXPORT()

#endif  // MCPCoreLogger_h
