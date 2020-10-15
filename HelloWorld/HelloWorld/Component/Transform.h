#pragma once
#include "Component.h"
#include "../Geometry/Vector3.h"
#include "../Geometry/Matrix4x4.h"

//Transform组件：负责几何变换
class Transform : public Component
{
	friend class Mesh;
public:
	Transform();
	//设置位置
	void SetPosition(Vector3 pos);
	//获取位置
	Vector3 GetPosition();
	//平移
	void Translate(Vector3 delta);
	//旋转
	void Rotate(Vector3 angle);

private:
	//模型变换矩阵
	Matrix4x4 model;
	//位置
	Vector3 position;
};
