//
//  IosVpnStateHandlerImpl.h
//  mobile_prometheus
//
//  Created by Dan Murphy on 6/14/15.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef __mobile_prometheus__IosVpnStateHandlerImpl__
#define __mobile_prometheus__IosVpnStateHandlerImpl__

#include <string>
#include "PlatformVpnStateHandlerImpl.h"

#import "PromClient.h"
#import "IosVpnStateHandlerDelegate.h"
#import "IosWidgetFrameDelegate.h"

#pragma GCC visibility push(default)
class IosVpnStateHandlerImpl : public PlatformVpnStateHandlerImpl {

public:

    IosVpnStateHandlerImpl(PlatformVpnStateHandlerImpl &javaImpl);

    static PlatformVpnStateHandlerImplPtr create(PromClient *pPromClient);

    virtual void stateChangeCb(int state);
    virtual void onErrorCallback(int severity, int status, const UserMessage &userMessage);
    virtual void onLogMessage(int level,
                              unsigned logClass,
                              const std::string &time,
                              const std::string &levelStr,
                              const std::string &classLabel,
                              const std::string &msg);
    virtual void readPersistentValue(int access_type,
                                            const std::string &key,StringHandler& );
    virtual void writePersistentValue(int access_type,
                                             const std::string &key,
                                             const std::string &value);
    virtual void deletePersistentValue(int access_type,
                                              const std::string &key);

    virtual void readPolicyPersistentValue(int access_type, const std::string &key,StringHandler& );
    virtual void writePolicyPersistentValue(int access_type,
                                             const std::string &key,
                                             const std::string &value);
    virtual void deletePolicyPersistentValue(int access_type,
                                              const std::string &key);
    virtual void onDiagnosticsConfigChanged(){};
    virtual void installSiteminderCredential(const std::string cookie, const std::string url);
    virtual ACSTATUS onVpnCredentialsRequest(std::shared_ptr<ICredentialResponseCB> &spCredResponseCB);


private:
    IosVpnStateHandlerImpl(PromClient *pPromClient);

    IosVpnStateHandlerImpl(const IosVpnStateHandlerImpl &other);
    IosVpnStateHandlerImpl &operator=(const IosVpnStateHandlerImpl &other);
    id<IosWidgetFrameDelegate> getWidgetDelegate();
};
#pragma GCC visibility pop

#endif /* defined(__mobile_prometheus__IosVpnStateHandlerImpl__) */
