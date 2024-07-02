//
//  IosStorageLocationProvider.h
//  MCPCore
//
//  Created by Richard Perry on 5/4/22.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef IosStorageLocationProvider_hpp
#define IosStorageLocationProvider_hpp

#import <Foundation/Foundation.h>
#include <string>
#include "IStorageLocationProvider.h"

#pragma GCC visibility push(default)
class IosStorageLocationProvider : public IStorageLocationProvider
{
public:
    IosStorageLocationProvider(NSDictionary <NSString *, NSString*>* config);
    std::string GetInternalStorageLocationPath() override;
    std::string GetSharedStorageLocationPathForIdentifier(const std::string &identifier) override;
private:
    std::string m_location;
};
#pragma GCC visibility pop

#endif /* IosStorageLocationProvider_hpp */
