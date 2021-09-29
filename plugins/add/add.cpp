/*
 * @Author: your name
 * @Date: 2021-08-09 09:14:38
 * @LastEditTime: 2021-08-10 18:08:31
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \plugin_loader\plugins\add\add.cpp
 */
#include "add.h"
#include <iostream>
const int TEST_CONST_VALUE = 100;
static int gTestStatic = 0;

int Add(int x, int y)
{
    auto result = x + y + 1;
    std::cout << result << std::endl;
    return result;
}
