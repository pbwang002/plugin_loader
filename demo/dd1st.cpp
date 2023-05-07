#include <iostream>
#include <string>
#include <algorithm>
// 不处理字符串超长或者没有正常结束符(\0)的情况，这个放在字符合法校验中
/*
 * 1. 指针为空时 按照 “0” 返回。
 * 2. 不处理超过 max_int的情况，自然截断处理，不处理字符串超长或者没有正常结束符(\0)的情况。
 * 3. 支持：a.正负号, b.前后空格, c.数字后面出现非法字符自动截断。
 */
int atoi (const char* pstr) 
{
    // 指针为空返回0
    if (pstr == nullptr) {
        return 0;
    }

    // 跳过前空格
    while (*pstr == ' ') {
        pstr++;
    }

    int ret = 0;
    int flag = 1;
    // 正负号支持
    if (*pstr == '-') {
        flag = -1;
    }
    if (*pstr == '-' || *pstr == '+') {
        pstr++;
    }

    // 非法字符截断，对于非数字字符，直接跳过，不用考虑\0的问题
    while (*pstr >= '0' && *pstr <= '9') {
        int temp = *pstr - '0';

        // 最大最小值处理 2147483647和 -2147483648，超过截断
        if (ret > INT32_MAX / 10) {
            return flag > 0 ? INT32_MAX : INT32_MIN;
        }
        if (ret == INT32_MAX / 10) {
            // 最大值截断
            if (flag > 0 && temp >= 7) {
                return INT32_MAX;
            }
            // 最小值截断
            if (flag < 0 && temp >= 8) {
                return INT32_MIN;
            }
        }
        ret = ret * 10 + temp;
        pstr++;
    }
    return ret * flag;
}
int main()
{
    char* input1 = nullptr;
    int ret1 = atoi(input1);
    std::cout << "NUll ptr : " << ret1 << std::endl;

    // 空格跳过
    char input2[100] = "   12324 ";
    int ret2 = atoi(input2);
    std::cout << "Skip blank : " << ret2 << std::endl;

    // 正号
    char input3[100] = "   +12324 ";
    int ret3 = atoi(input3);
    std::cout << "Positive value : " << ret3 << std::endl;

    // 负号
    char input4[100] = "   -12324 ";
    int ret4 = atoi(input4);
    std::cout << "Minus value : " << ret4 << std::endl;

    // 最大越界
    char input5[100] = "   +1234567891111 ";
    int ret5 = atoi(input5);
    std::cout << "Out max : " << ret5 << std::endl;

    // 最小越界
    char input6[100] = "   -1234567891111 ";
    int ret6 = atoi(input6);
    std::cout << "Out min : " << ret6 << std::endl;

    // 非法截断
    char input7[100] = "   -12345test ";
    int ret7 = atoi(input7);
    std::cout << "Illegeal test : " << ret6 << std::endl;
    return 0;
}