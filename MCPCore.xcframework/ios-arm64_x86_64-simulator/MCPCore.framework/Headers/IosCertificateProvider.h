//
//  IosCertificateProvider.h
//  mstapnext_injectable_ios
//
//  Created by Paul Tillotson 3/12/18.
//  Copyright © 2018 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef IosCertificateProvider_h
#define IosCertificateProvider_h


#include "atlas_client_types.h"
#include "IPlatformCertificateProvider.h"
#include "AtlasCryptoProvider.h"

#pragma GCC visibility push(default)
class IosCertificateProvider : public IPlatformCertificateProvider,
                               private IExternalCertificateStore
{
public:
    IosCertificateProvider();

    virtual ~IosCertificateProvider() override = default;

    // IPlatformCertificateProvider virtual method overrides
    virtual ACSTATUS ProvisionTrustedServerCerts(const AtlasTrustedServerCertCollection &serverCerts,
                                                 bool blockNetworkResources) override;
    virtual IExternalCertificateStore *GetExternalCertificateStore() override;

    // IExternalCertificateStore virtual method overrides
    virtual ACSTATUS VerifyCertificateTrust(const std::vector<std::vector<uint8_t>> &certChain,
                                            const std::vector<std::vector<uint8_t>> &extraCACerts,
                                            const char *unusedHostnameOrAddrStr,
                                            const char *unusedCipherSpec) override;
};
#pragma GCC visibility pop
#endif /* IosCertificateProvider_h */
