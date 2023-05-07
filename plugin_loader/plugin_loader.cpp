#include <dlfcn.h>
#include <iostream>
#include "plugin_loader.h"
const int gPluginLoaderFlag = RTLD_NOW | RTLD_GLOBAL;
PluginLoader::PluginLoader(const std::string& path)
{
    LoadPlugin(path);
}
PluginLoader::~PluginLoader()
{
    UnLoadPlugin();
}
int PluginLoader::LoadPlugin(const std::string& path)
{
    handle_ = dlopen(path.c_str(), gPluginLoaderFlag);
    if (handle_ == nullptr) {
        std::cout << "Open plugin failed, " << dlerror() << std::endl;
    }
    return 0;
}
int PluginLoader::UnLoadPlugin()
{
    int ret = dlclose(handle_);
    if (ret != 0) {
        std::cout << "close plugin failed, error code is " << ret << std::endl; 
    }
    return ret;
}

void* PluginLoader::GetFunc(const std::string& symbol)
{
    auto it = funcMapping_.find(symbol);
    if (it != funcMapping_.end() && it->second != nullptr) {
        return it->second;
    }

    auto funcPtr = dlsym(handle_, symbol.c_str());
    if (funcPtr == nullptr) {
        std::cout << "Get symbol failed, " << dlerror() << std::endl;
        return nullptr;
    }

    funcMapping_[symbol] = funcPtr; 
    return funcPtr;
}
