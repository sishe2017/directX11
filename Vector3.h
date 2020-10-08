#pragma once
#include "Vector2.h"
#include <initializer_list>


class Vector3 :
    public Vector2
{
    friend Vector3 operator+(Vector3 v1, Vector3 v2);
    friend Vector3 operator-(Vector3 v1, Vector3 v2);

public:
    Vector3();
    Vector3(float x, float y, float z);
    Vector3(std::initializer_list<float> initList);
    Vector3& operator+=(Vector3 v);

    float z;

protected:
    //更新向量值
    void UpdateValue() override;
};

