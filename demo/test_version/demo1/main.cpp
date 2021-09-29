/*
 * @Author: your name
 * @Date: 2021-08-09 20:12:20
 * @LastEditTime: 2021-08-09 20:18:46
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \plugin_loader\demo\global_symbol_iterpose\main.cpp
 */
#include <iostream>
#include <thread>
// __asm__(".symver getVersionV1,getVersion@VER1.0");
// __asm__(".symver getVersionV2,getVersion@VER2.0");
extern "C" {
    int c1();
    int c2();
}

int main()
{
    std::cout << c1() << std::endl;
    std::cout << c2() << std::endl;
    // std::cout << getVersionV2() << std::endl;
    return 0;
}