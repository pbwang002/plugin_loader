#include <algorithm>
#include "plugin_manager.h"

int PluginManager::LoadPlugins(const std::vector<std::string>& pluginPaths)
{
    for (const auto& it : pluginPaths) {
        LoadPlugin(it);
    }
    return 0;
}
std::shared_ptr<PluginLoader> PluginManager::LoadPlugin(const std::string& pluginPath)
{
    auto pluginit = pathPluginMapping_.find(pluginPath);
    if (pluginit == pathPluginMapping_.end()) {
        pathPluginMapping_[pluginPath] = std::move(std::make_shared<PluginLoader>(pluginPath));
    }
    return pathPluginMapping_[pluginPath];   
}
int PluginManager::unloadPlugins(const std::vector<std::string>& pluginPaths)
{
    for (const auto& it : pluginPaths) {
        auto plugin = pathPluginMapping_.find(it);
        if (plugin != pathPluginMapping_.end()) {
            pathPluginMapping_.erase(plugin);
        }
    }
    return 0;
}
