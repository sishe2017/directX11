#pragma once
#include <initializer_list>
#include <DirectXMath.h>


class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(std::initializer_list<float> initList);

	//x坐标
	float x;
	//y坐标
	float y;

protected:
	//DirectXMath类型的向量
	DirectX::XMVECTOR vector;
	//更新向量值
	virtual void UpdateValue();
};

