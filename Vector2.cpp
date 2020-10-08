#include "Vector2.h"

using namespace std;
using namespace DirectX;

Vector2::Vector2():
	x(0),
	y(0)
{
	vector = XMVectorZero();
}

Vector2::Vector2(float x, float y):
	x(x),
	y(y)
{
	vector = XMVectorSet(x, y, 0.0f, 0.0f);
}

Vector2::Vector2(std::initializer_list<float> initList)
{
	auto p = initList.begin();
	this->x = *p;
	p++;
	this->y = *p;

	vector = XMVectorSet(x, y, 0.0f, 0.0f);
}

//更新向量值
void Vector2::UpdateValue()
{
	this->x = XMVectorGetX(vector);
	this->y = XMVectorGetY(vector);
	
}
