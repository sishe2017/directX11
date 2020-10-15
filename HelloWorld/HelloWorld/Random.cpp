#include "Random.h"
#include <random>

//生成范围内的随机整数（左闭右开）
int Random::RangeInt(int start, int end)
{
    return (rand() % (end - start)) + start;
}

//生成范围内的浮点数（左闭右开）
float Random::RangeFloat(float start, float end)
{
    //生成整数部分
    int integer = RangeInt(static_cast<int>(start), static_cast<int>(end));
    //生成小数部分
    float decimal = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

    return static_cast<float>(integer) + decimal;
}
