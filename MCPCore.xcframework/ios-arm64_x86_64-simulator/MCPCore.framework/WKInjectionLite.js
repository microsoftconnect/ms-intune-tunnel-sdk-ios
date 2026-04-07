//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//

/* jshint esversion: 6 */
/* jslint bitwise: true */
function mstobject() {  // eslint-disable-line no-unused-vars
    return window.mstobject;
}

// Use an anonymous function that we call in-line as a namespace for injection
(function () {
    // will be filled at injection time
    var ecs = %@ || {};
    var httpLogLevel = %d;

    function generateUUID() {
        var uuid = crypto.randomUUID();
        if (uuid) return uuid;

        return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function (c) {
                var r = Math.random() * 16 | 0, v = c == 'x' ? r : (r & 0x3 | 0x8);
                return v.toString(16);
            });
    }

    class MstLogger {
        __logLevel = httpLogLevel;
        constructor(context, id) {
            this.__context = context || "";
            this.__id = id || "";
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

        logDebugData(action, data) {
            if (typeof (data) === "string") {
                this.logDebug(action + ` string, length = ` + data.length);
            }
            else if (typeof (data) === "object") {
                if (data instanceof Blob) {
                    data.arrayBuffer().then((buffer)=>{
                        this.logDebug(action + ` Blob, length = ` + buffer.byteLength);
                    });
                }
                else if (data instanceof DataView) {
                    var bytes = new Uint8Array(data.buffer);
                    this.logDebug(action + ` DataView, length = ` + bytes.byteLength);
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

                        var bytes = new Uint8Array(data.buffer);
                        this.logDebug(action + ` TypedArray, length = ` + bytes.byteLength);
                }
                else if (data instanceof ArrayBuffer) {
                    this.logDebug(action + ` ArrayBuffer, length = ` + data.byteLength);
                }
                else {
                    this.logError(action + ` unsupported type`);
                }
            }
        }

        __log(logFunc, level, message) {
            var consolePrefix = `[${new Date().toISOString()}][MicrosoftTunnel][${level}]`;
            var logMessage = `[${this.__context}][${this.__id}] ${message}`;
            logFunc(consolePrefix + logMessage);
            webkit.messageHandlers.mstCallbackHandler.postMessage({ 'action': 'logMessage', 'level': level, 'message': logMessage });
        }
    };

    mstobject().webSocketLogger = new MstLogger("WebSocket"); // Global logger used by evaluated web socket js scripts.

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

    mstobject().websockets = {};
    class MstWebSocket extends EventTarget {
        constructor(url, protocols) {
            super();
            this.CONNECTING = MstWebSocket.CONNECTING;
            this.OPEN = MstWebSocket.OPEN;
            this.CLOSING = MstWebSocket.CLOSING;
            this.CLOSED = MstWebSocket.CLOSED;
            this.__tag = generateUUID();
            this.__bufferedAmount = 0;
            this.binaryType = "blob";
            this.url = url;
            this.__logger = new MstLogger("WebSocket", this.__tag);
            this.__logger.logInfo(`constructor '${url}' - '${protocols}' - '${window.location.origin}' - '${navigator.userAgent}'`);
            const baseURI = document.baseURI || window.location.href || "";
            this.__post({'method': 'constructor', 'url': url, 'protocols': protocols, 'origin': window.location.origin, 'baseURI': baseURI, 'userAgent': navigator.userAgent});
            mstobject().websockets[this.__tag] = this;
        }

        static get CONNECTING() { return 0; }
        static get OPEN() { return 1; }
        static get CLOSING() { return 2; }
        static get CLOSED() { return 3; }

        send(data) {
            this.__logger.logDebugData('Send', data);

            if (typeof (data) === "string") {
                this.__bufferedAmount += data.length;
                this.__post({'method': 'send', 'isBinary': false, 'data': data});
            }
            else if (typeof (data) === "object") {
                if (data instanceof Blob) {
                    data.arrayBuffer().then((buffer) => {
                        this.__bufferedAmount += buffer.byteLength;
                        var encodedData = this.__arrayBufferToBase64(buffer);
                        this.__post({'method': 'send', 'isBinary': true, 'data': encodedData});
                    }).catch((error) => {
                        this.__logger.logError(`Failed to convert Blob to ArrayBuffer: ${error}`);
                        this.dispatchEvent(new ErrorEvent('error', { 'message': 'Failed to convert Blob to ArrayBuffer' }));
                        return Promise.reject(error);
                    });
                }
                else if (data instanceof DataView) {

                    var bytes = new Uint8Array(data.buffer);
                    this.__bufferedAmount += bytes.byteLength;

                    var encodedData = this.__uintArrayToBase64(bytes)
                    this.__post({'method': 'send', 'isBinary': true, 'data': encodedData});
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

                    var bytes = new Uint8Array(data.buffer);
                    this.__bufferedAmount += bytes.byteLength;

                    var encodedData = this.__uintArrayToBase64(bytes)
                    this.__post({'method': 'send', 'isBinary': true, 'data': encodedData});
                }
                else if (data instanceof ArrayBuffer) {
                    this.__bufferedAmount += data.byteLength;
                    var encodedData = this.__arrayBufferToBase64(data)
                    this.__post({'method': 'send', 'isBinary': true, 'data': encodedData});
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
            var buffer = this.__base64ToArrayBuffer(message);
            this.__logger.logDebugData('Receive', buffer);

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
            const fixedFields = { 'action': 'webSocket', 'tag': this.__tag };
            const mergedMessage = { ...message, ...fixedFields };
            webkit.messageHandlers.mstCallbackHandler.postMessage(mergedMessage);
        }

        __uintArrayToBase64(bytes) {
            var binary = '';
            var len = bytes.byteLength;
            for (var i = 0; i < len; i++) {
                binary += String.fromCharCode(bytes[i]);
            }
            return window.btoa(binary);
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
    }

    WebSocket = MstWebSocket;
    webkit.messageHandlers.mstCallbackHandler.postMessage({ 'action': 'webSocket', 'method': "clearSockets" });

    mstobject().webSocketLogger.logInfo('Intercepting web sockets');

    if (ecs.interceptJSFormData || ecs.interceptJSRequestBody) {
        var fetchLogger = new MstLogger("Fetch");
        var interceptLogger = new MstLogger("Intercept");

        var nativeSend = XMLHttpRequest.prototype.send;
        var nativeOpen = XMLHttpRequest.prototype.open;
        var nativeFetch = fetch;


        async function formDataToArrayBuffer(formData) {
          const encoder = new TextEncoder();
          const boundary = '----WebKitFormBoundary' + Math.random().toString(36).substr(2);

          const chunks = [];

          for (const [name, value] of formData.entries()) {
            chunks.push(encoder.encode(`--${boundary}\r\n`));
            if (value instanceof File) {
              const fileHeader = `Content-Disposition: form-data; name="${name}"; filename="${value.name}"\r\n` +
                                 `Content-Type: ${value.type || 'application/octet-stream'}\r\n\r\n`;
              chunks.push(encoder.encode(fileHeader));
              chunks.push(new Uint8Array(await value.arrayBuffer()));
              chunks.push(encoder.encode('\r\n'));
            } else {
              const fieldHeader = `Content-Disposition: form-data; name="${name}"\r\n\r\n`;
              chunks.push(encoder.encode(fieldHeader));
              chunks.push(encoder.encode(value + '\r\n'));
            }
          }

          chunks.push(encoder.encode(`--${boundary}--\r\n`));

          // Concatenate all chunks into a single ArrayBuffer
          const totalLength = chunks.reduce((acc, chunk) => acc + chunk.length, 0);
          const buffer = new Uint8Array(totalLength);
          let offset = 0;
          for (const chunk of chunks) {
            buffer.set(chunk, offset);
            offset += chunk.length;
          }

          return {
            arrayBuffer: buffer.buffer,
            contentType: `multipart/form-data; boundary=${boundary}`
          };
        }

        function sendRequest(body, input, options, contentType, send) {
            if (input != null) {
                // fetch() call
                if (options == null) {
                    options = {};
                }
                options.body = body;

                if (input instanceof Request) {
                    input = new Request(input, options);
                }
            }

            return send(body, input, options, contentType);
        }

        function interceptBody(body, input, options, passthrough) {
            if (body == null) {
                body = '';
            }

            if (body instanceof Document) {
                if (body.documentElement != null) {
                    body = body.documentElement.outerHTML;
                } else {
                    body = '';
                }
            }

            if (typeof body === "object") {
                if (body instanceof FormData) {
                    interceptLogger.logInfo('Intercepting FormData');
                    return formDataToArrayBuffer(body)
                    .then(result => {
                        return sendRequest(result.arrayBuffer, input, options, result.contentType, passthrough);
                    })
                    .catch(error => {
                        interceptLogger.logError('Error when reading FormData: ' + error);
                        return Promise.reject(error);
                    });
                }

                if (body instanceof ReadableStream && input instanceof Request) {
                    interceptLogger.logInfo('Intercepting ReadableStream');
                    return input.arrayBuffer()
                    .then(array => {
                        return sendRequest(array, input, options, null, passthrough);
                    })
                    .catch(error => {
                        interceptLogger.logError('Error when reading ReadableStream: ' + error);
                        return Promise.reject(error);
                    });
                }

                if (body instanceof Blob) {
                    interceptLogger.logInfo('Intercepting Blob');
                    return body.arrayBuffer()
                    .then(array => {
                        return sendRequest(array, input, options, null, passthrough);
                    })
                    .catch(error => {
                        interceptLogger.logError('Error when reading Blob: ' + error);
                        return Promise.reject(error);
                    });
                }

                interceptLogger.logInfo('Passing through object type:' + body.constructor.name);
            }

            if (typeof body === 'string') {
              const encoder = new TextEncoder();
              body = encoder.encode(body).buffer;
            }

            return passthrough(body, input, options, null);
        }

        if (ecs.interceptJSRequestBody) {
            fetchLogger.logInfo('Intercepting fetch()');

            fetch = function (input, options) {
                var body = "";
                var method = "";
                if (typeof input === typeof "") {
                    fetchLogger.logInfo('fetch() with URL');

                    if (options == null) {
                        // No body, no headers, just send the request.
                        return nativeFetch(input, options);
                    }

                    body = options.body;
                    method = options.method;
                } else {
                    fetchLogger.logInfo('fetch() with Request');
                    body = input.body
                    method = input.method;
                }

                // We only want to handle requests with a body
                if (!body) {
                    return nativeFetch(input, options);
                }

                return interceptBody(body, input, options, (b, i, o, c) => {
                    // Update content type if needed.
                    if (c) {
                        if (!o) o = {};
                        o = { ...o, headers: { ...o.headers, 'Content-Type': c } };
                    }
                    return nativeFetch(i, o);
                });
            };
        }

        XMLHttpRequest.prototype.open = function(method, url) {
            this._mstMethod = method;
            this._mstUrl = url;
            this._mstTag = generateUUID();
            this._mstLogger = new MstLogger("XHR", this._mstTag);
            return nativeOpen.apply(this, arguments);
        };

        XMLHttpRequest.prototype.send = function(body) {
            var xhr = this;
            var method = this._mstMethod || "GET";
            var url = this._mstUrl || "";
            var tag = this._mstTag || generateUUID();
            var logger = this._mstLogger;

            // We only want to handle requests with a body
            if (!body) {
                return nativeSend.call(xhr, body);
            }

            logger.logInfo('Intercepting XMLHttpRequest send()');

            if (ecs.interceptJSRequestBody) {
                if (!(body instanceof FormData) || !ecs.interceptJSFormData) {
                    return interceptBody(body, null, null, (b, i, o, c) => {
                        // Update content type if needed.
                        if (c) { xhr.setRequestHeader('Content-Type', c); }
                        return nativeSend.call(xhr, b);
                    });
                }
            }

            if (!(body instanceof FormData) || method.toUpperCase() != "POST" || !ecs.interceptJSFormData) {
                return nativeSend.call(xhr, body);
            }

            logger.logInfo('Marshalling XMLHttpRequest FormData');

            // Intercept XMLHttpRequest POST requests with FormData bodies for multipart/form-data reconstruction
            var MST_TUNNEL_ID_HEADER = 'X-Msft-Tunnel-Id';

            // Inject custom header with UUID for lookup later
            xhr.setRequestHeader(MST_TUNNEL_ID_HEADER, tag);
            logger.logInfo('Injected ' + MST_TUNNEL_ID_HEADER + ' header with tag: ' + tag);

            // Handle POST requests with FormData bodies
            var formArr = [];
            var pending = 0;
            var done = false;

            // Serialize the FormData
            for (var pair of body.entries()) {
                if (!(pair[1] instanceof Blob)) {
                    formArr.push({ key: pair[0], value: pair[1] });
                    continue;
                }

                // Handle Blob/File fields with async processing
                pending++;
                (function(key, blob) {
                    var reader = new FileReader();
                    reader.onload = function() {
                        logger.logInfo('Processing file');
                        var uint8Array = new Uint8Array(reader.result);

                        // Convert to base64 in chunks to avoid stack overflow on large files
                        var binaryString = '';
                        var chunkSize = 8192; // Process 8KB chunks
                        for (var i = 0; i < uint8Array.length; i += chunkSize) {
                            var chunk = uint8Array.subarray(i, i + chunkSize);
                            binaryString += String.fromCharCode.apply(null, chunk);
                        }

                        var base64Data = btoa(binaryString);
                        formArr.push({
                            key: key,
                            filename: blob.name || 'unknown', // Preserve original filename
                            type: blob.type || 'application/octet-stream',
                            data: base64Data
                        });

                        pending--;
                        if (pending === 0 && done) sendFormData();
                    };
                    reader.onerror = function(e) {
                        logger.logError('FileReader error: ' + (e.target && e.target.error && e.target.error.message ? e.target.error.message : 'Unknown error'));
                        pending--;
                        if (pending === 0 && done) sendFormData();
                    };
                    reader.readAsArrayBuffer(blob);
                })(pair[0], pair[1]);
            }

            done = true;
            // If no async operations are pending, send immediately
            if (pending === 0) sendFormData();

            // Function to send the serialized FormData to the native bridge
            function sendFormData() {
                logger.logInfo('Sending FormData to native bridge - entries: ' + formArr.length);
                try {
                    webkit.messageHandlers.mstCallbackHandler.postMessage({
                        action: "formDataSend",
                        url: url,
                        content: JSON.stringify(formArr),
                        encoding: "formdata-serialized",
                        tag: tag
                    });
                    return nativeSend.call(xhr, null);
                } catch (e) {
                    logger.logInfo('Bridge communication failed: ' + (e.message ? e.message : e.toString()));
                    // Fallback: send original request if bridge fails
                    return nativeSend.call(xhr, body);
                }
            }
        };
    }
}());

