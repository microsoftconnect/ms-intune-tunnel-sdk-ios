//
//  PlatformDispatcherBridge.h
//  mstapnext
//
//  Created by Richard Perry on 5/4/22.
//

#include "CFSourceDispatchQueue.h"
#include "PlatformDispatcherBase.h"

#ifndef PlatformDispatcherBridge_h
#define PlatformDispatcherBridge_h

// bridge from C++ to Objective-C
class PlatformDispatcherBridge : public virtual IDispatcher,
                                 public CFSourceDispatchQueue
{
public:
    PlatformDispatcherBridge(CFRunLoopRef runLoop)
        : CFSourceDispatchQueue(runLoop)
    {
        // Intentionally blank
    }

    virtual ~PlatformDispatcherBridge()
    {
        // Intentionally blank
    }
};

#endif /* PlatformDispatcherBridge_h */
