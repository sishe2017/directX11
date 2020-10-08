#include "Transform.h"

Transform::Transform()
{
	
}

//设置位置
void Transform::SetPosition(Vector3 pos)
{
	//计算当前位置到目标位置的距离
	auto distance = pos - this->position;
	//平移距离
	Translate(distance);
}

//平移
void Transform::Translate(Vector3 delta)
{
	//更新位置
	position += delta;
	//更新变换矩阵
	model *= Matrix4x4::Translation(delta);
}

//旋转
void Transform::Rotate(Vector3 angle)
{
	//更新变换矩阵
	model *= Matrix4x4::Rotation(angle);
}
