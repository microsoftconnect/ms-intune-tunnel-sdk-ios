//
//  IosAssetProvider.h
//  MCPCore
//
//  Created by Tim Champagne Jr on 4/27/22.
//

#ifndef IosAssetProvider_h
#define IosAssetProvider_h

#import <Foundation/Foundation.h>

#include <string>
#include <vector>
#include <cstdint>

#include "IAssetProvider.h"
#include "MCPServiceBase.h"

#pragma GCC visibility push(default)

// Note: the concrete IosAssetProvider is an IMCPService to allow access to non-virtual methods that are not part of
//   the IAssetProvider interface. The IAssetProvider interface is *not* an IMCPService (as of yet)
class IosAssetProvider : public MCPServiceBase<IosAssetProvider>,
                         public IAssetProvider
{
public:
    using base_type = MCPServiceBase<IosAssetProvider>;

    IosAssetProvider(IMCPServices &service,
                     Class clsForBundle);

    NSString *GetFilePath(const std::string &relativeAssetPath);
    std::string Read(const std::string &normalizedAssetPath) override;
    void ReadBytes(const std::string &normalizedAssetPath, std::vector<uint8_t> &outBytes) override;

private:
    NSString *getFilePath(const std::string &normalizedAssetPath);

    Class m_clsForBundle;
};

#pragma GCC visibility pop

#endif  // IosAssetProvider_h
