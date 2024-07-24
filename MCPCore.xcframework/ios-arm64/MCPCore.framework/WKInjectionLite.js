//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//

// Designed to be visible to other apps, hence outside the anonymous function
// Currently being used by the PTA/automation for a sanity test

/* jshint esversion: 6 */
/* jslint bitwise: true */
// Use an anonymous function that we call in-line as a namespace for injection
(function () {
    window.mstobject.injected = false;
    var cookieSetterOrig = document.__lookupSetter__('cookie');
    var cookieGetterOrig = document.__lookupGetter__('cookie');
    Object.defineProperty(document, 'cookie', {
        get: function () {
            return cookieGetterOrig.apply(document);
        },
        set: function (cookie) {
            var originUrl = location.href;
            webkit.messageHandlers.mstCallbackHandler.postMessage({ 'action': 'setCookie', 'url': originUrl, 'cookie': cookie });
            cookieSetterOrig.apply(document, arguments);
        },
        configurable: true
    });
}());
