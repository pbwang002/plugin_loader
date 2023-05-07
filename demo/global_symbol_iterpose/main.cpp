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
void b1();
void b2();

int main()
{
    b1();
    b2();
    while(1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}