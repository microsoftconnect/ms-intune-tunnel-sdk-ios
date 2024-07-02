//
//  IosNotificationProvider.h
//  mstapnext_injectable_ios
//
//  Created by Connor Kelley 12/1/17.
//  Copyright © 2017 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef IosNotificationProvider_h
#define IosNotificationProvider_h

#include <Foundation/Foundation.h>

#include "IPlatformNotificationProvider.h"

NSString * const kUrlKey = @"urlKey";

#pragma GCC visibility push(default)
class IosNotificationProvider : public IPlatformNotificationProvider {
  public:
    IosNotificationProvider();

  protected:
    virtual ACSTATUS OnNotificationReceived(const std::string &title,
                                            const std::string &body,
                                            const std::string &urlToOpen,
                                            const std::string &identifier) override;
    virtual bool ShouldHandleNotificationWithIdentifier(const std::string &identifier) override;
    virtual void HandleNotificationResponse(const NOTIFICATION_RESPONSE response,
                                            const std::string &title,
                                            const std::string &body,
                                            const std::string &urlToOpen,
                                            const std::string &identifier) override;
    virtual ~IosNotificationProvider() override = default;

  private:
    NSMutableArray *mMstNotificationIdentifiers;
};
#pragma GCC visibility pop

#endif /* IosNotificationProvider_h */
