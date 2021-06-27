#include <string>
#include <vector>
#include "plugin_loader/plugin_loader.h"
#include <memory>
class PluginManager {
public:
    int LoadPlugins(const std::vector<std::string>& pluginPaths);
    std::shared_ptr<PluginLoader> LoadPlugin(const std::string& pluginPath);
    int unloadPlugins(const std::vector<std::string>& pluginPaths);
private:
    std::unordered_map<std::string, std::shared_ptr<PluginLoader>> pathPluginMapping_; 
};
