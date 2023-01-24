//
//  IosNetworkReachabilityImpl.h
//  Compass
//
//  Created by Tim Champagne Jr. on 12/4/15.
//  Copyright © 2015 Mocana. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef IosNetworkReachabilityImpl_h
#define IosNetworkReachabilityImpl_h

#include <memory>
#include <string>
#include "locks.h"

#include "cxx_compat.h"

#import <SystemConfiguration/SystemConfiguration.h>

#import "PolicyGateEventHandler.h"
#import "PlatformNetworkReachabilityImpl.h"
#import "ProtectedData.h"

class PromClient;
class IosNetworkReachabilityImpl;

//

static constexpr size_t kServerReachabilityRefPos = 0;
static constexpr size_t kLocalAddrReachabilityRefPos = 1;
static constexpr size_t kWasLocalPos = 2;

using ReachabilityProtectedData = ProtectedData<
    SCNetworkReachabilityRef, SCNetworkReachabilityRef, bool
>;

//
#pragma GCC visibility push(default)
class IosNetworkReachabilityImpl : public PlatformNetworkReachabilityImpl
{
 public:
    static PlatformNetworkReachabilityPtr create();

    IosNetworkReachabilityImpl();
    virtual ~IosNetworkReachabilityImpl();

    void HandleReachabilityChange(SCNetworkReachabilityRef target, SCNetworkReachabilityFlags flags);

    // PlatformNetworkReachabilityImpl virtual method overrides
    virtual void StartReachabilityMonitoring() override;
    virtual void StopReachabilityMonitoring() override;

    virtual void OnContacting() override;
    virtual void OnDisconnected() override;

    virtual void OnLocalAddressChanged(const std::string &localAddress) override;

    virtual void NotifyCurrentReachability() override;

    virtual void LogInterfaces() override;

 private:
    bool isReachable();
    bool isReachable(SCNetworkReachabilityFlags flags);
    bool isLocal(SCNetworkReachabilityFlags flags);

    void startReachabilityMonitoringForServer();
    void stopReachabilityMonitoringForServer();

    void startReachabilityMonitoringForLocalAddr(const std::string &localAddress);
    void stopReachabilityMonitoringForLocalAddr();

    void notifyReachability(const SCNetworkReachabilityFlags flags,
                            const bool notifyLocal);

    // helpers that operate on passed private data and expect to be passed a
    // pre-acquired guard
    bool startReachabilityMonitoringForRef(ReachabilityProtectedData::Guard &guard,
                                           SCNetworkReachabilityRef ref);
    void stopReachabilityMonitoringForRef(ReachabilityProtectedData::Guard &guard,
                                          SCNetworkReachabilityRef ref);
    void notifyCurrentReachabilityAsync(ReachabilityProtectedData::Guard &guard,
                                        SCNetworkReachabilityRef ref,
                                        int64_t nsecDelay = 0);
    bool shouldNotifyLocal(ReachabilityProtectedData::Guard &guard,
                             SCNetworkReachabilityRef target);

    ReachabilityProtectedData m_data;
};
#pragma GCC visibility pop

#endif /* IosNetworkReachabilityImpl_h */
