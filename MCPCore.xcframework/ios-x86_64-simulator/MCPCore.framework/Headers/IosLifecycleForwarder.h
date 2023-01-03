//
//  IosLifecycleForwarder.h
//  mstapnext_injectable_ios
//
//  Created by Tim Champagne Jr. on 6/26/17.
//  Copyright © 2017 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef IosLifecycleForwarder_h
#define IosLifecycleForwarder_h

#include "ForwardedState.h"
#include "PlatformLifecycleForwarderBase.h"

/**
 * iOS 9 doesn't have a scheduleTimer signature that takes a block, so jump
 * through a bunch of hoops to allow us to schedule an NSTimer from from C++.
 */
// @{

@interface TimerBridge : NSObject

+ (TimerBridge *)scheduledTimerWithTimeInterval:(NSTimeInterval)interval repeats:(BOOL)repeats block:(void (^)(NSTimer *timer))block;

- (void)onTimerFired:(NSTimer *)timer;

@property (nonatomic, strong) void (^block)(NSTimer *timer);
@property (nonatomic, weak) NSTimer *timer;

@end

// @}

class MstLoadReplayer;

#pragma GCC visibility push(default)
class IosLifecycleForwarder : public PlatformLifecycleForwarderBase
{
public:
    using base_type = PlatformLifecycleForwarderBase;

    IosLifecycleForwarder();
    virtual ~IosLifecycleForwarder() override = default;

    virtual ACSTATUS onAppPerformBackgroundFetch(const EventNotification &eventNotification) override;

    virtual bool ForwardAppBackgrounding() override;
    virtual bool ForwardAppForegrounding() override;
    virtual bool ForwardAppResigningActive() override;
    virtual bool ForwardAppBecomingActive() override;

    virtual ACSTATUS FastForward() override;

    virtual ACSTATUS PerformAppTransition() override;

    virtual ACSTATUS onAppStart(const EventNotification &eventNotificaiton) override;
    virtual ACSTATUS onAppControl(const EventNotification &eventNotificaiton) override;

    virtual void appExit() override;

protected:
    MstLoadReplayer *mstlLoader;
    void tryForwardAppPerformingBackgroundFetch();
    void forwardProtectedDataAvailable();
    void forwardProtectedDataUnavailable();

    void appBackgroundFetchTimedOut();

    void destroyBackgroundFetchTimer();
    void addBackgroundFetchTimer();

    bool forwardSelector(SEL selector, NSNotificationName notificationName);
    bool forwardSceneSelector(SEL selector, NSNotificationName notificationName);
    bool m_canPerformBlock;
    bool m_gotBackgroundFetch;
    bool m_forwardedProtectedDataAvailable;
    TimerBridge *m_backgroundFetchTimer;
};

#pragma GCC visibility pop
#endif /* IosLifecycleForwarder_h */
