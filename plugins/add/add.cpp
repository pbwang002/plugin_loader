#include "add.h"
#include <iostream>
const int TEST_CONST_VALUE = 100;
static int gTestStatic = 0;

int Add(int x, int y)
{
    auto result = x + y;
    std::cout << result << std::endl;
    return result;
}
