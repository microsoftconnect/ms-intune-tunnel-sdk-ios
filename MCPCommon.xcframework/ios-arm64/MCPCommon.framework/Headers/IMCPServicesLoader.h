//
//  IMCPServicesLoader.h
//  MCPCommon
//
//  Created by Tim Champagne Jr on 2/28/22.
//  Copyright © 2022 Blue Cedar Networks. All rights reserved.
//  Licensed to Microsoft under Contract #7267038.
//
#ifndef IMCPServicesLoader_h
#define IMCPServicesLoader_h

#include <utility>

#include "IMCPServices.h"
#include "IMCPPluginLoaderService.h"

MCP_BEGIN_EXPORT()

// Note: this does not need to be a singleton, but the underlying PluginLoader is accessed as one today.
class IMCPServicesLoader
{
public:
    virtual ~IMCPServicesLoader() = default;

    /**
     * Get a weak pointer to the IMCPServices instance that will be used by the services loader as
     * the home for any loaded services.
     *
     * @note This pointer is not guaranteed to remain valid beyond the lifetime of the
     *   IMCPServicesLoader. To release ownership of the IMCPServices instance after plugin loading
     *   has been completed, use ReleaseMCPServices.
     *
     * @return a weak IMCPServices pointer
     */
    virtual IMCPServices *GetWeakMCPServices() = 0;

    // SWIG doesn't deal well with returning smart pointers
#ifndef SWIG
    /**
      * Release ownership of the the IMCPServices instance that will be used by the services loader as
      * the home for any loaded services. This allows the caller to continue to use the IMCPServices
      * instance beyond the lifetime of the services loader itself.
      *
      * @return a weak IMCPServices pointer
      */
    virtual SmarterPtr<IMCPServices> ReleaseMCPServices() = 0;
#endif

    /*
     * Populates the service loader's IMCPServices instance with services from plugins located in pluginPaths by opening
     * those plugins and invoking their autoLoad methods. This method can be used as a convenience in place of
     * OpenPluginsForServices if there are no special ordering requirements related to plugin loading.
     *
     * @note the IMCPServices instance containing the loaded services can be retrieved using {@link #GetWeakMCPServices()} or
     *   {@link #ReleaseMCPServices()}. See those methods for details about IMCPServices lifetimes.
     *
     * @param pluginPaths the paths to open and load plugins from
     * @param pPluginObserver optional pointer to an IPluginObserver that can be used to observe the loaded plugins.
     *
     * @return true on success, false on failure.
     */
    virtual bool InitAndAutoLoadServices(const std::vector<std::string> &pluginPaths,
                                         IPluginObserver *pPluginObserver = nullptr) = 0;

    // SWIG doesn't deal well with returning smart pointers
#ifndef SWIG
    /*
     * Creates a new IMCPServices instance (if pPreExistingMCPServices is nullptr) and a plugin loader service, which is
     * used to open plugins from pluginPaths. The plugin libraries will be loaded, but will not have their autoLoad
     * methods invoked. This gives the caller an opportunity to interact with IMCPServices before plugin autoLoad, to
     * pre-register services needed by plugins, mediate plugin load order, etc.
     *
     * When using this method rather than AutoLoadServices, the caller is responsible for ensuring the autoLoad methods
     * are invoked for all plugins, either individually or all at once. Because of the additional responsibility, it is
     * recommended to use MCPServicesLoader::AutoLoadServices when possible.
     *
     * @param pluginPaths the paths to open and load plugins from
     * @param pPluginObserver optional pointer to an IPluginObserver that can be used to observe the loaded plugins.
     *
     * @return On success, an IMCPPluginLoaderService that may be used by the caller to finish loading the plugins by using
     *   AutoLoadAll to auto-load all plugins or by calling LoadPlugin on the individual plugins. On error, an empty SmarterPtr.
     */
    virtual SmarterPtr<IMCPPluginLoaderService> InitAndOpenPluginsForServices(const std::vector<std::string> &pluginPaths,
                                                                              IPluginObserver *pPluginObserver = nullptr) = 0;
#endif

protected:
    IMCPServicesLoader() = default;
};

MCP_END_EXPORT()

#endif  // IMCPServicesLoader_h
