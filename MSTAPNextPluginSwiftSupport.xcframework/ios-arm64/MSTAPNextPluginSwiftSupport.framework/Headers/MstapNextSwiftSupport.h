//
//  MstapNextSwiftSupport.h
//  MSTAPNextPluginSwiftSupport
//
//  Created by Richard Perry on 6/29/21.
//  Copyright © 2021 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#include <dispatch/dispatch.h>

#ifdef __cplusplus

#include "SwiftSupportProviderPlugin.h"

class MapnextSwiftSupportProvider : public SwiftSupportProviderPlugin
{
public:
    void initSwiftRelinks() override;
protected:
    MapnextSwiftSupportProvider(){};
    virtual ~MapnextSwiftSupportProvider(){};

    ACSTATUS initComponent() override;
};

extern "C"
{
#endif  // __cplusplus

void *GetOriginalMakeFileSystemObjectSource();
void *GetBypassMakeFileSystemObjectSource();

dispatch_source_type_t GetSwiftDispatchSourceTypeVnode();

#ifdef __cplusplus
}
#endif
