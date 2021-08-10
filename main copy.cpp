/*
 * @Author: your name
 * @Date: 2021-08-09 22:41:21
 * @LastEditTime: 2021-08-10 15:00:07
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \plugin_loader\main copy.cpp
 */
#include <iostream>
#include <string>
#include <thread>
#include "plugin_manager/plugin_manager.h"
#include "plugins/add/add.h"

typedef int (*ADD)(int x, int y);
int main()
{
    std::string basePluginPath = "/mnt/d/learn/test002/plugin_loader/build/lib/";
    std::string addPlugin = "libadd.so";
    PluginManager pluginManager;
    auto plugin = pluginManager.LoadPlugin(basePluginPath + addPlugin);
    auto addFunc = (ADD)plugin->GetFunc("Add");
    auto ret = addFunc(1, 2);
    std::cout << ret << std::endl;

    // auto ret = Add(1, 2);
    // while (true) {
    //     std::this_thread::sleep_for(std::chrono::milliseconds(2));
    // }
    
    return 0;
}
