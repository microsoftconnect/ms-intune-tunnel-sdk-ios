// Designed to be visible to other apps, hence outside the anonymous function
// Currently being used by the PTA/automation for a sanity test
function mstobject() {  // eslint-disable-line no-unused-vars
    return window.mstobject;
}

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

    function __mstGetTag() {
        return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function (c) {
            var r = Math.random() * 16 | 0, v = c == 'x' ? r : (r & 0x3 | 0x8);
            return v.toString(16);
        });
    }

    function __mstLog(content) {
        var log = content;
        webkit.messageHandlers.mstCallbackHandler.postMessage({ 'action': 'log', 'content': log });
    }

    function interceptBody(body, input, options) {
        if ((undefined === body) || (null === body)) {
            body = '';
        }

        var sendBody = body;
        if (body instanceof Document) {
            if (body.documentElement !== null) {
                sendBody = body.documentElement.outerHTML;
            } else {
                sendBody = '';
            }
        }

        if (typeof body === "object") {
            if (body instanceof FormData) {
                var boundary = function () {
                    function s4() {
                        var n = Math.floor((1 + Math.random()) * 0x10000);
                        return n.toString(16).substring(1);
                    }
                    return "----WebKitFormBoundary" + s4() + s4() + s4() + s4();
                }();

                var CRLF = '\r\n';
                var blob_parts = [];
                var entries_it = body.entries();
                while (true) {                      // eslint-disable-line no-constant-condition 
                    var it = entries_it.next();
                    if (it.done) {
                        break;
                    }
                    var key = it.value[0];
                    var value = it.value[1];
                    blob_parts.push('--' + boundary + CRLF);
                    blob_parts.push('Content-Disposition: form-data; name="' + key + '"');
                    if (value instanceof Blob) {
                        var blobContentType = value.type || 'application/octet-stream';
                        blob_parts.push('; filename="' + value.name + '"' + CRLF);
                        blob_parts.push('Content-Type: ' + blobContentType + CRLF + CRLF);
                        blob_parts.push(value);
                        blob_parts.push(CRLF);
                    } else {
                        blob_parts.push(CRLF + CRLF + value + CRLF);
                    }
                }
                blob_parts.push('--' + boundary + '--' + CRLF);
                sendBody = new Blob(blob_parts);
            }
            if (body instanceof ReadableStream) {
                // TODO: implement stream requests in an async manner, which we don't have a good way to do currently.
                return;
            }
            if (body instanceof Blob) {
                var outerThis = this;
                var filereader = new FileReader();
                filereader.onload = function () {
                    if ((undefined === options) || (null === options)) {
                        input.body = this.result;
                    } else {
                        options.body = this.result;
                    }
                    outerThis.fetch(input, options);
                };
                filereader.readAsArrayBuffer(body);
                // The FileReader load is async, so bail from here.
                // The recursive call will send in an ArrayBuffer
                return;
            }

            // ArrayBufferView is a namesake, the real classes are
            if (body instanceof Int8Array ||
                body instanceof Uint8Array ||
                body instanceof Uint8ClampedArray ||
                body instanceof Int16Array ||
                body instanceof Uint16Array ||
                body instanceof Int32Array ||
                body instanceof Uint32Array ||
                body instanceof Float32Array ||
                body instanceof Float64Array) {
                // Get the underlying ArrayBuffer, allow next if statement to process
                sendBody = body.buffer;
            }

            if (body instanceof ArrayBuffer) {
                var bytes = new Uint8Array(body);
                // Cast off original for actual call to send
                sendBody = JSON.parse('{"bytes":[' + bytes.toString() + ']}');
            }
        }

        if (typeof (body) === "string") {
            webkit.messageHandlers.mstCallbackHandler.postMessage({ 'action': 'ajaxSend', 'tag': this.__mstUrl, 'method': this.__mstMethod, 'content': body });
        } else if (typeof (body) === "object") {
            webkit.messageHandlers.mstCallbackHandler.postMessage({ 'action': 'ajaxSend', 'tag': this.__mstUrl, 'method': this.__mstMethod, 'content': JSON.stringify(body) });
            // Reset original for actual call to send.
            // Only benefit here is that Web Inspector shows a more accurate result
            body = sendBody;
        }
        return sendBody;
    }

    self.mstFetch = self.fetch;
    self.fetch = function (input, options) {
        // spec found here: https://fetch.spec.whatwg.org/
        var body = "";

        if (typeof input === typeof "") {
            __mstLog("fetch with URL")
            // input is url
            this.__mstUrl = input;

            if ((undefined === options) || (null === options)) {
                // no body, no headers, just send the request.
                return this.mstFetch(input)
            }

            body = options.body;
        } else {
            __mstLog("fetch with Request")
            this.__mstUrl = input.url;
            body = input.body;
        }

        var result = interceptBody(body, input, options);

        if ((undefined === result) || (null === result)) {
            return;
        }

        return this.mstFetch(input, options);
    }

    XMLHttpRequest.prototype.mstOpen = XMLHttpRequest.prototype.open;
    XMLHttpRequest.prototype.open = function () {
        // remember the request tag and method for sending to the UIProcess
        // This tag will be set as a MST-Request header that we will strip out in the ProxmetheusURLProtocol
        // Beacause we aren't actually modifying anything, access what we need by position
        // and then forward the whole Arguments object.
        // METHOD ( arguments[0] ) and URL (arguments[1] ) are guaranteed to be present,
        // async ( arguments[2] ), username ( arguments[3] ), and password ( arguments[4] ) are all optional
        this.__mstTag = __mstGetTag();
        this.__mstMethod = arguments[0];
        this.__mstUrl = arguments[1];
        __mstLog('Tagging url: ' + arguments[1] + ' with tag: ' + this.__mstTag);
        return this.mstOpen.apply(this, arguments);
    };

    XMLHttpRequest.prototype.mstSend = XMLHttpRequest.prototype.send;
    XMLHttpRequest.prototype.send = function (body) {
        // Send can be called without a body, which can result in a 411 if the content length is not set to 0.
        // To fix this, we need to set the body to be empty ("") which causes the client to do the right thing.
        if ((undefined === body) || (null === body)) {
            body = "";
        }

        // Add code to monitor and honor failed CORS requests here
        // Code used to exist that watched for exceptions and attempted to forward events, 
        // however the existing code was causing issues with SAP apps for both Colgate and Molex.
        // Created AC-5156 to track this task.

        // There are a few types of input body types:
        // - string
        // - Document (convert to string)
        // - Blob (convert to ArrayBuffer via FileReader)
        // - ArrayBufferView (convert to ArrayBuffer)
        // - ArrayBuffer (convert to byte array)
        // - FormData (needs proper construction)

        var sendBody = null;
        if (body instanceof Document) {
            if (body.documentElement !== null) {
                body = body.documentElement.outerHTML;
            } else {
                body = '';
            }
        }

        if (typeof (body) === "object") {
            if (body instanceof FormData) {
                var boundary = function () {
                    function s4() {
                        var n = Math.floor((1 + Math.random()) * 0x10000);
                        return n.toString(16).substring(1);
                    }
                    return "----WebKitFormBoundary" + s4() + s4() + s4() + s4();
                }();

                var CRLF = '\r\n';
                var blob_parts = [];
                var entries_it = body.entries();
                while (true) {                      // eslint-disable-line no-constant-condition
                    var it = entries_it.next();
                    if (it.done) {
                        break;
                    }
                    var key = it.value[0];
                    var value = it.value[1];
                    blob_parts.push('--' + boundary + CRLF);
                    blob_parts.push('Content-Disposition: form-data; name="' + key + '"');
                    if (value instanceof Blob) {
                        var blobContentType = value.type || 'application/octet-stream';
                        blob_parts.push('; filename="' + value.name + '"' + CRLF);
                        blob_parts.push('Content-Type: ' + blobContentType + CRLF + CRLF);
                        blob_parts.push(value);
                        blob_parts.push(CRLF);
                    } else {
                        blob_parts.push(CRLF + CRLF + value + CRLF);
                    }
                }
                blob_parts.push('--' + boundary + '--' + CRLF);
                body = new Blob(blob_parts);
            }
            if (body instanceof Blob) {
                var outerThis = this;
                var filereader = new FileReader();
                filereader.onload = function () {
                    outerThis.send(this.result);
                };
                filereader.readAsArrayBuffer(body);
                // The FileReader load is async, so bail from here.
                // The recursive call will send in an ArrayBuffer
                return;
            }

            // ArrayBufferView is a namesake, the real classes are
            if (body instanceof Int8Array ||
                body instanceof Uint8Array ||
                body instanceof Uint8ClampedArray ||
                body instanceof Int16Array ||
                body instanceof Uint16Array ||
                body instanceof Int32Array ||
                body instanceof Uint32Array ||
                body instanceof Float32Array ||
                body instanceof Float64Array) {
                // Get the underlying ArrayBuffer, allow next if statement to process
                body = body.buffer;
            }
            if (body instanceof ArrayBuffer) {
                var bytes = new Uint8Array(body);
                // Cast off original for actual call to send
                sendBody = body;
                body = JSON.parse('{"bytes":[' + bytes.toString() + ']}');
            }
        }

        if (typeof (body) === "string") {
            webkit.messageHandlers.mstCallbackHandler.postMessage({ 'action': 'ajaxSend', 'tag': this.__mstUrl, 'method': this.__mstMethod, 'content': body });
        } else if (typeof (body) === "object") {
            webkit.messageHandlers.mstCallbackHandler.postMessage({ 'action': 'ajaxSend', 'tag': this.__mstUrl, 'method': this.__mstMethod, 'content': JSON.stringify(body) });
            // Reset original for actual call to send.
            // Only benefit here is that Web Inspector shows a more accurate result
            body = sendBody;
        }

        this.mstSend(body);
    };

    // Save original HTMLFormElement functions to call submit for non-events
    HTMLFormElement.prototype.mstSubmit = HTMLFormElement.prototype.submit;

    // Override HTMLFormElement function for non-events
    HTMLFormElement.prototype.submit = function () {
        // We got in here via the submit action.
        // We need to scrape the form data and then, since we have replaced it, call the original submit.
        scrapeFormData(this, "submit");
        // The true tells the function that we came from an intercepted submit, and not the event listener
        this.mstSubmit();
    };

    function scrapeFormData(form, source) {
        var jsonArr = [];
        for (var i = 0; i < form.elements.length; i++) {
            var parName = form.elements[i].name;
            var parValue = form.elements[i].value;
            var parType = form.elements[i].type;
            // HTML 4.01 spec defines the concept of a "successful control" that define what form
            // elements should be included inside
            // Ref: https://www.w3.org/TR/html401/interact/forms.html#h-17.13.2
            var isSuccessfulControl = true;
            if (parType.toLowerCase() == "radio") {
                isSuccessfulControl = form.elements[i].checked;
            } else if (parType.toLowerCase() == "checkbox") {
                isSuccessfulControl = form.elements[i].checked;
            } else if (parType.toLowerCase() == "option") {
                isSuccessfulControl = form.elements[i].selected;
            } else if (parType.toLowerCase() == "button") {
                isSuccessfulControl = false;
            } else if (parType.toLowerCase() == "submit") {
                // The form should use the name/value of the control that submitted it.
                // We got this information through our click handler, so look for the tag we set.
                // Reset it back to undefined for the future.
                if (form.elements[i].__mstSubmitted === true) {
                    // var content = "Submit: " + parName + " value: " + parValue;
                } else {
                    // Otherwise ignore it, there can be multiple submit buttons and we only want the one that got clicked
                    isSuccessfulControl = false;
                }
            } else if (parValue === undefined) {
                isSuccessfulControl = false;
            } else if (form.elements[i].disabled) {
                isSuccessfulControl = false;
            }
            if (isSuccessfulControl) {
                jsonArr.push({
                    name: parName,
                    value: parValue,
                    type: parType
                });
            }
        }

        var action = form.action;
        if (action === undefined || action === "") {
            action = window.location.href;
        }

        // log the way that we got this information. It could be used in the future, but currently is just
        // more information for debugging.
        webkit.messageHandlers.mstCallbackHandler.postMessage({ 'action': 'formContent', 'url': action, 'source': source, 'content': jsonArr });

    }

    // Register submit event listener.
    // The "true" sets the listener to capture, which will fire before any bubbling,
    // which protects us from javascript calling preventDefault() on the event or returning false
    // All we need to do is scrape the form data in line.
    window.addEventListener('submit', function (e) {
        scrapeFormData(e.target, "before");
    }, true);

    // (ckelley) Gross hack... some javascript attempts to protect against javascript scraping by setting significant
    // elements in their own onsubmit handler. This attempts to put itself at the end and scrape the final result.
    // Because anything can stop the bubbling, we still need to have a listener at the beginning as well.
    // This will overwrite any incomplete information in the WKWebViewBridge
    // See https://stackoverflow.com/questions/22873122/jmeter-cant-sign-in-to-the-app-that-uses-google-auth
    window.addEventListener('submit', function (e) {
        scrapeFormData(e.target, "after");
    }, false);

    // Because there submit action does not provide the submit button, we need a click listener
    // When a click happens, get an up to date list of the submit buttons/inputs and mark the one that was clicked
    // We need to check for contains() because sometimes the click target is nested inside the element, not the element itself
    window.addEventListener('click', function (e) {
        var buttons = Array.prototype.slice.call(document.querySelectorAll("button[type=submit]"), 0);
        var inputs = Array.prototype.slice.call(document.querySelectorAll("input[type=submit]"), 0);
        var inputElements = buttons.concat(inputs);
        for (var i = 0; i < inputElements.length; i++) {
            // To protect against double presses, clear out any previous marking
            inputElements[i].__mstSubmitted = null;
            // If the button contains the target, the click occured inside of the tag.
            // Mark it as the submit button. We can then break, since there can only be one.
            if (inputElements[i].contains(e.target)) {
                inputElements[i].__mstSubmitted = true;
                break;
            }
        }
    }, true);
    __mstLog('Done loading MST JavaScript');
    window.mstobject.injected = true;
}());
