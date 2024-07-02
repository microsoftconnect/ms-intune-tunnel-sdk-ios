//
//  IosSecureDataProvider.h
//  mstapnext_injectable_ios
//
//  Created by Sujan Kota on 1/14/16.
//  Copyright © 2016 Mocana. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef IosSecureDataProvider_h
#define IosSecureDataProvider_h

#import "MstapNextSecureDataProvider.h"
#import "time.h"

class IPlatformSecureDataProviderCB;

#pragma GCC visibility push(default)
class IosSecureDataProvider : public MstapNextSecureDataProvider
{
public:
    IosSecureDataProvider(PlatformPerpReportImpl *pPlatformPerpReportImpl);
    virtual ~IosSecureDataProvider() override { };

    time_t GetFirstLaunchTime();
    std::string GetAppBundleID();

    virtual ACSTATUS HandleSecureDataVersions(const unsigned int versionFromKeystore,
                                              const unsigned int versionFromBulkStorage) override;
    
private:
    class SecureDataSource;
    class BiometricSource;
    class PlatformKeySource;

    IosSecureDataProvider(const IosSecureDataProvider&) = delete;
    IosSecureDataProvider& operator=(const IosSecureDataProvider&) = delete;

    // IPlatformSecureDataProvider virtual method overrides
    virtual ACSTATUS delegateInit() override;

    time_t m_firstLaunchTime;
    std::string m_appBundleID;
};
#pragma GCC visibility pop

#endif /* IosSecureDataProvider_h */
