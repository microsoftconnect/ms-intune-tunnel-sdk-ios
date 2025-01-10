//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//

// Designed to be visible to other apps, hence outside the anonymous function
// Currently being used by the PTA/automation for a sanity test

/* jshint esversion: 6 */
/* jslint bitwise: true */
function mstobject() {  // eslint-disable-line no-unused-vars
    return window.mstobject;
}

// Use an anonymous function that we call in-line as a namespace for injection
(function () {
    window.mstobject.injected = false;
    
    // will be filled at injection time
    mstobject().ecs = %@ || {};
    mstobject().httpLogLevel = %d;
    
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
    
    class MstLogger {
        __logLevel = mstobject().httpLogLevel;
        constructor(tag) {
            this.__tag = tag;
        }
        logDebug(message) {
            if (this.__logLevel > 0) { return; }
            this.__log(console.log, "DEBUG", message);
        }
        
        logInfo(message) {
            if (this.__logLevel > 1) { return; }
            this.__log(console.log, "INFO", message);
        }
        
        logWarn(message) {
            if (this.__logLevel > 2) { return; }
            this.__log(console.log, "WARN", message);
        }
        
        logError(message) {
            if (this.__logLevel > 3) { return; }
            this.__log(console.error, "ERROR", message);
        }
        
        __log(logFunc, level, message) {
            logFunc(`[${new Date().toISOString()}][MicrosoftTunnel][${this.__tag}][${level}] ${message}`);
        }
    };
    
    if (mstobject().ecs.webSocketsEnabled) {
        mstobject().websockets = {};
        class MstWebSocket extends EventTarget {
            constructor(url, protocols) {
                super();
                this.CONNECTING = MstWebSocket.CONNECTING;
                this.OPEN = MstWebSocket.OPEN;
                this.CLOSING = MstWebSocket.CLOSING;
                this.CLOSED = MstWebSocket.CLOSED;
                this.__tag = this.__createTag();
                this.binaryType = "blob";
                this.url = url;
                this.__logger = new MstLogger("WebSocket");
                this.__logger.logInfo(`constructor '${url}' - '${protocols}' - '${window.location.origin}' - '${navigator.userAgent}'`);
                this.__post({'method': 'constructor', 'url': url, 'protocols': protocols, 'origin': window.location.origin, 'userAgent': navigator.userAgent});
                mstobject().websockets[this.__tag] = this;
            }
            
            static get CONNECTING() { return 0; }
            static get OPEN() { return 1; }
            static get CLOSING() { return 2; }
            static get CLOSED() { return 3; }
            
            send(data) {
                if (typeof (data) === "string") {
                    this.__logger.logDebug(`send string`);
                    this.__post({'method': 'send', 'isBinary': false, 'data': data});
                }
                else if (typeof (data) === "object") {
                    if (data instanceof Blob) {
                        this.__logger.logDebug(`send Blob`);
                        data.arrayBuffer().then((buffer)=>{
                            this.__post({'method': 'send', 'isBinary': true, 'data': this.__arrayBufferToBase64(buffer)});
                        });
                    }
                    else if (data instanceof DataView) {
                        this.__logger.logDebug(`send DataView`);
                        this.__post({'method': 'send', 'isBinary': true, 'data': this.__arrayBufferToBase64(data.buffer)});
                    }
                    else if (data instanceof Int8Array ||
                             data instanceof Uint8Array ||
                             data instanceof Uint8ClampedArray ||
                             data instanceof Int16Array ||
                             data instanceof Uint16Array ||
                             data instanceof Int32Array ||
                             data instanceof Uint32Array ||
                             data instanceof Float32Array ||
                             data instanceof Float64Array ||
                             data instanceof BigInt64Array ||
                             data instanceof BigUint64Array) {
                        this.__logger.logDebug(`send TypedArray`);
                        this.__post({'method': 'send', 'isBinary': true, 'data': this.__arrayBufferToBase64(data.buffer)});
                    }
                    else if (data instanceof ArrayBuffer) {
                        this.__logger.logDebug(`send ArrayBuffer`);
                        this.__post({'method': 'send', 'isBinary': true, 'data': this.__arrayBufferToBase64(data)});
                    }
                    else {
                        this.__logger.logError(`send unsupported type`);
                        this.dispatchEvent(new ErrorEvent('error', { 'message': 'Unsupported type sent to "send"'}));
                    }
                }
            }
            
            close(code = 1000, reason) {
                this.__logger.logInfo(`Client close '${code}' - '${reason}'`);
                this.__post({'method': 'close', 'code': code, 'reason': reason});
            }
            
            set onopen(handler){
                this.__logger.logInfo(`Client onopen set`);
                this.addEventListener.apply(this, ['open', handler, false]);
            }
            
            set onmessage(handler){
                this.__logger.logInfo(`Client onmessage set`);
                this.addEventListener.apply(this, ['message', handler, false]);
            }
            set onclose(handler){
                this.__logger.logInfo(`Client onclose set`);
                this.addEventListener.apply(this, ['close', handler, false]);
            }
            set onerror(handler){
                this.__logger.logInfo(`Client onerror set`);
                this.addEventListener.apply(this, ['error', handler, false]);
            }
            
            __close(options) {
                options = options || {};
                options.wasClean = (options.code === 1000 || options.code === 1005);
                this.__logger.logInfo(`Server close '${options.code}' - '${options.reason}'`);
                this.dispatchEvent(new CloseEvent('close', options));
                this.__logger.logDebug(`Stopped tracking websocket '${this.__tag}'`);
                delete mstobject().websockets[this.__tag];
            }
            
            __binaryMessage(message){
                this.__logger.logDebug(`Server binary message received. binaryType = '${this.binaryType}'.`);
                var buffer = this.__base64ToArrayBuffer(message);
                var options = { 'origin': this.url };
                if (this.binaryType === "arraybuffer") {
                    options.data = buffer;
                }
                else { //assume default of blob
                    options.data = new Blob([buffer]);
                }
                
                this.dispatchEvent(new MessageEvent('message', options));
            }
            
            __post(message){
                webkit.messageHandlers.mstCallbackHandler.postMessage({ 'action': 'webSocket', 'tag': this.__tag, ...message });
            }
            
            __arrayBufferToBase64(buffer) {
                var binary = '';
                var bytes = new Uint8Array(buffer);
                var len = bytes.byteLength;
                for (var i = 0; i < len; i++) {
                    binary += String.fromCharCode(bytes[i]);
                }
                return window.btoa(binary);
            }
            
            __base64ToArrayBuffer(base64) {
                var binaryString = atob(base64);
                var bytes = new Uint8Array(binaryString.length);
                for (var i = 0; i < binaryString.length; i++) {
                    bytes[i] = binaryString.charCodeAt(i);
                }
                return bytes.buffer;
            }
            
            __createTag() {
                return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function (c) {
                    var r = Math.random() * 16 | 0, v = c == 'x' ? r : (r & 0x3 | 0x8);
                    return v.toString(16);
                });
            }
        }
        
        var OriginalWebSocket = WebSocket;
        WebSocket = MstWebSocket;
        webkit.messageHandlers.mstCallbackHandler.postMessage({ 'action': 'webSocket', 'method': "clearSockets" });
    }
}());
