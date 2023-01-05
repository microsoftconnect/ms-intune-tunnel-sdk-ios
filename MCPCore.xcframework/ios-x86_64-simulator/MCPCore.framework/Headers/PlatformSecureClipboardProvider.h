//
//  ISecureClipboardProvider.h
//  mstapnext_injectable_ios
//
//  Created by Vadim Lozko. on 5/31/16.
//  Copyright © 2016 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//

#ifndef ISecureClipboardProvider_h
#define ISecureClipboardProvider_h

#include <string>
#include <memory>
#include "PolicyGateTypes.h"
#include "IMCPComponent.h"

#pragma GCC visibility push(default)

class ISecureClipboardProvider : public IMCPComponent
{
public:
    virtual ~ISecureClipboardProvider() {}

    /**
     * Recipients of this callback should sync with the contents of the system
     * clipboard and then start clipboard interception.
     */
    virtual void StartCopyPasteInterception(bool copyBlocked, bool pasteBlocked) = 0;

    /**
     * Recipients of this callback should stop interception of the system
     * clipboard.
     */
    virtual void StopCopyPasteInterception() = 0;

    /**
     * Recipients of this callback should block/unblock drag and drop.
     */
    virtual void StartDragDropInterception(bool dragBlocked, bool dropBlocked) {};
    
    virtual std::string GetSecureClipboardName() { return ""; };

    virtual void ClearSecureClipboard() {};

    virtual void StoreEncodedSecureClipboardData(const std::string &data) = 0;
    virtual ACSTATUS LoadEncodedSecureClipboardData(std::string &outData) = 0;
    virtual std::string LoadEncodedSecureClipboardData() = 0;

};

#pragma GCC visibility pop

#endif /* ISecureClipboardProvider_h */
