//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//

/*
 * For consistency, make the entire script a single anonymous function.
 *
 * Overall, this will be more portable because then we will awlays be
 * running in a functional context where 'return' can be used rather
 * than hoping we are at script/global scope where a call to exit would
 * be the only way to exit without further evaluation.
 */

/* Alter a few media prototypes */
(function()
{
    function isServerRunning()
    {
        if (window.mstMediaPlayer !== undefined)
        {
            return window.mstMediaPlayer.isServerRunning;
        }
        else if (window.mst_map_injectedObject !== undefined)
        {
            return window.mst_map_injectedObject.isMediaPlayerRunning();
        }
        return false;
    }

    function getServerPort()
    {
        if (window.mstMediaPlayer !== undefined)
        {
            return window.mstMediaPlayer.port;
        }
        else if (window.mst_map_injectedObject !== undefined)
        {
            return window.mst_map_injectedObject.getMediaPlayerPort();
        }
        return -1;
    }

    function getServerURL()
    {
        return 'http://127.0.0.1:' + getServerPort();
    }
    
    function replaceSrcAttributeForNode(node)
    {
        var orig_src = node.getAttribute('src');
        if (!orig_src)
        {
            return false;
        }
        
        if (orig_src.lastIndexOf(getServerURL(), 0) === 0)
        {
            return false;
        }

        if (!orig_src.startsWith("http:") && !orig_src.startsWith("https:"))
        {
            return false;
        }

        var l = document.createElement('a');
        l.href = orig_src;
        var src_base = l.protocol + "//" + l.hostname;
        if (l.port)
        {
            src_base += ":" + l.port;
        }
        var new_src = getServerURL() + l.pathname;
        new_src += (l.search !== "" ? l.search + "&" : "?");
        new_src += "__x_map_redirect=" + encodeURIComponent(src_base);
        node.setAttribute('src', new_src);
        return true;
    }
    
    HTMLMediaElement.prototype._replaceSrcAttributes = function()
    {
        if (isServerRunning() === false)
        {
            return false;
        }

        var outResult = replaceSrcAttributeForNode(this);
        
        var source_children = this.getElementsByTagName('source');
        for (var i = 0; i < source_children.length; i++)
        {
            var n = source_children[i];
            var localResult = replaceSrcAttributeForNode(n);
            if (localResult)
            {
                outResult = true;
            }
        }
        return outResult;
    };
        
    HTMLMediaElement.prototype._mstLoad = HTMLMediaElement.prototype.load;
    HTMLMediaElement.prototype.load = function()
    {
        this._replaceSrcAttributes();
        this._mstLoad();
    };

    HTMLMediaElement.prototype._mstPlay = HTMLMediaElement.prototype.play;
    HTMLMediaElement.prototype.play = function()
    {
        var result = this._replaceSrcAttributes();
        if (result)
        {
            /*
             * If the call to replaceSrcAttributes returns true, then an
             * actual change was made, which means we must reload the source.
             *
             * Additionally, any prior playback state must be cleared.
             */
            this._mstLoad();
            this._previous_currentTime = 0;
        }
        
        if (this._previous_currentTime > 0)
        {
            /* If we had a previous currentTime, then handle separately. */
            var loadMetaDataFunc = function(e)
            {
                /* When metadata is loaded, seek and play */
                var media = e.target;
                media.currentTime = media._previous_currentTime;
                media._mstPlay();
                media._previous_currentTime = 0;
                media.removeEventListener('loadedmetadata', loadMetaDataFunc);
            };
            this.addEventListener('loadedmetadata', loadMetaDataFunc);
            this._mstLoad();
            return;
        }
        
        this._mstPlay();
    };
    
    HTMLMediaElement.prototype._wasPreviouslyPlaying = function()
    {
        /*
         * There is no singular function to check if a media is playing,
         * so the typical method involves checking four elements:
         *  !ended - media has not finished
         *  !paused - Has not been paused
         *  this.currentTime > 0 - Has actually started playback
         *  this.readyState >= 2 - The 'readyState' indicates that we have data
         *       2, HAVE_CURRENT_DATA
         *       3, HAVE_FUTURE_DATA
         *       4, HAVE_ENOUGH_DATA
         *
         * Unfortunately, when the app is backgrounded iOS automatically pauses
         * the media (such that the 'paused' attribute will return true) but not
         * a 'hard' pause such that when the app comes back from the background
         * the media playback will resume immediately.
         *
         * Therefore, we simply have to ignore the 'pause' check here, using the
         * remaining three checks to ensure that the media was actually playing
         * at one time.  This is safe to do because calling pause on an already
         * paused media has no visible effect (aside from turn the prior 'soft'
         * pause into a 'hard' pause).
         */
        
        if (!this.ended &&
            this.currentTime > 0 &&
            this.readyState >= 2)
        {
            return true;
        }
        return false;
    };
    
    HTMLMediaElement.prototype._mstInterrupt = function()
    {
        /*
         * If the media was previously playing, then we want to 'hard' pause
         * and record the time that the media was previously at.
         */
        if (this._wasPreviouslyPlaying())
        {
            this._previous_currentTime = this.currentTime;
            this.pause();
        }
    };
    
    HTMLMediaElement.prototype._onCreate = function()
    {
        if (this._mstOnCreateCalled === true)
        {
            return;
        }

        this._mstOnCreateCalled = true;

        /* Perform an initial set of replacements */
        this._replaceSrcAttributes();
        
        /*
         * Establish a full subtree attribute observer for the
         * media element. This observer will watch the entire
         * subtree media down for changes to 'src' attributes.
         *
         * When a change is detected, we will invoke the
         * replaceSrcAttributes function to make sure that
         * all src attributes are still pointing to the
         * LocalMediaServer.
         */
        var observerFunction = function(mutations, observer)      // eslint-disable-line no-unused-vars
        {
            var m = mutations[0];
            var target = m.target;
            if (target.tagName.toLowerCase() == 'source')
            {
                target = target.parentElement;
            }
            if (target._replaceSrcAttributes !== undefined)
            {
                target._replaceSrcAttributes();
            }
        };
        var properties = {attributes:true, attributeFilter:['src'], subtree: true};
        (new MutationObserver(observerFunction)).observe(this, properties);

        /*
         * Lastly, add a listener for the "mst_background" event
         * so any videos that were playing can be paused.
         */

        var backgroundListener = function(e)
        {
            e.target._mstInterrupt();
        };
        this.addEventListener('mst_background', backgroundListener);
    };
    
    
    /*
     * In order to catch media tags that have been created by DOM parsing,
     * we must look out for this event, and seek out the elements manually.
     *
     * This event is fired BEFORE any media activity occurs, including prior
     * to the loading of metadata or anything of the sort.
     
     * Ideally, the _onCreate method will be sufficient when media is made
     * both by DOM parsing and by 'createElement' calls, though time may
     * show a need for those implementations to remain distinct.
     *
     */

    var inspectElementForMedia = function(elem)
    {
        if (elem.getElementsByTagName === undefined)
        {
            return;
        }

        var videos = elem.getElementsByTagName('video');
        for (var i = 0; i < videos.length; i++)
        {
            videos[i]._onCreate();
        }

        var audios = elem.getElementsByTagName('audio');
        for (var j = 0; j < audios.length; j++)
        {
            audios[j]._onCreate();
        }
    };

    var firstLoadEvent = function()
    {
        inspectElementForMedia(document);
    };

    var watchDocumentChanges = function(mutations, observer)    // eslint-disable-line no-unused-vars
    {
        for (var i = 0; i < mutations.length; i++)
        {
            var m = mutations[i];
            for (var j = 0; j < m.addedNodes.length; j++)
            {
                inspectElementForMedia(m.addedNodes[j]);
            }
        }
    };

    var properties = {childList:true, subtree:true};
    (new MutationObserver(watchDocumentChanges).observe(document, properties));


    // this breaks a ton of functionality in amazon and other sites.
    // For the life of me I can't see a benefit to doing this this way, so commenting it out for now
    // document._mstCreateElement = document.createElement;
    // document.createElement = function()
    // {
    //     element = this._mstCreateElement.apply(this, arguments);
    //     if (element._onCreate !== undefined)
    //     {
    //         element._onCreate();
    //     }
    //     return element;
    // };

    /*
     * We must listen at the *window* level because the document object
     * gets changed based on what state the page is in when this script
     * is run.  The window, on the other hand, cannot change.
     */
    window.addEventListener('DOMContentLoaded', function(e) { firstLoadEvent(); });  // eslint-disable-line no-unused-vars
})();
