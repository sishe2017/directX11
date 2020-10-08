#include "Vector3.h"
#include <DirectXMath.h>

using namespace std;
using namespace DirectX;

Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->vector = XMVectorZero();
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->vector = XMVectorSet(x, y, z, 0.0f);
}

Vector3::Vector3(std::initializer_list<float> initList)
{
	auto it = initList.begin();
	x = *it;
	it++;
	y = *it;
	it++;
	z = *it;
	this->vector = XMVectorSet(x, y, z, 0.0f);
}

Vector3& Vector3::operator+=(Vector3 v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;

	return *this;
}

void Vector3::UpdateValue()
{
	this->x = XMVectorGetX(vector);
	this->y = XMVectorGetY(vector);
	this->z = XMVectorGetZ(vector);
}

//三维向量相加
Vector3 operator+(Vector3 v1, Vector3 v2)
{
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3 operator-(Vector3 v1, Vector3 v2)
{
	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

