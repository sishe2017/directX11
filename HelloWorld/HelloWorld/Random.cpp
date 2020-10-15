#include "Random.h"
#include <random>

//���ɷ�Χ�ڵ��������������ҿ���
int Random::RangeInt(int start, int end)
{
    return (rand() % (end - start)) + start;
}

//���ɷ�Χ�ڵĸ�����������ҿ���
float Random::RangeFloat(float start, float end)
{
    //������������
    int integer = RangeInt(static_cast<int>(start), static_cast<int>(end));
    //����С������
    float decimal = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

    return static_cast<float>(integer) + decimal;
}
