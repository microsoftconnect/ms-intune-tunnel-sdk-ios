//
//  MCP_CoreManagerHolder.h
//  MCPCore
//
//  Created by Richard Perry on 3/29/22.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef MCP_CoreManagerHolder_h
#define MCP_CoreManagerHolder_h

#include <stdio.h>
#include <memory>

#include "MstapNextCoreManager.h"
#include "MCP.h"

MCP_BEGIN_EXPORT()

class MstapNextInterception;
struct ConfigProfile;

class MCP_CoreManagerHolder {
    
public:
    MCP_CoreManagerHolder();
    static MCP_CoreManagerHolder* mainHolder();
    MstapNextInterception* getMstapNextInterception();
    std::shared_ptr<ConfigProfile> getCurrentProfile();
    void setCoreManager(MstapNextCoreManager* manager);
    MstapNextCoreManager *getCoreManager();
private:
    MstapNextCoreManager *coreManager;
};

MCP_END_EXPORT()

#endif /* MCP_CoreManagerHolder_h */
