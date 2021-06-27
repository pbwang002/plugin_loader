#include <iostream>
#include <string>
#include "plugin_manager/plugin_manager.h"

typedef int (*ADD)(int x, int y);
int main()
{
    std::string basePluginPath = "/mnt/d/code/code_hub/plugin_loader/build/lib/";
    std::string addPlugin = "libadd.so";
    PluginManager pluginManager;
    auto plugin = pluginManager.LoadPlugin(basePluginPath + addPlugin);
    auto add_func = (ADD)plugin->GetFunc("Add");
    auto ret = add_func(1, 2);
    std::cout << ret << std::endl;
    return 0;
}
