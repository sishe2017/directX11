#pragma once
#include <initializer_list>
#include <DirectXMath.h>


class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(std::initializer_list<float> initList);

	//x����
	float x;
	//y����
	float y;

protected:
	//DirectXMath���͵�����
	DirectX::XMVECTOR vector;
	//��������ֵ
	virtual void UpdateValue();
};

