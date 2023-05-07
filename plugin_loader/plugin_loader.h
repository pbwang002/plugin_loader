#ifndef PLUGIN_LOADER_H
#define PLUGIN_LOADER_H
#include <string>
#include <unordered_map>
class PluginLoader {
public:
    PluginLoader(const std::string& path);
    ~PluginLoader();
    void* GetFunc(const std::string& symbol);
private:
    int LoadPlugin(const std::string& path);
    int UnLoadPlugin();   
private:
    void *handle_{nullptr};
    std::unordered_map<std::string, void*> funcMapping_;
};
#endif
