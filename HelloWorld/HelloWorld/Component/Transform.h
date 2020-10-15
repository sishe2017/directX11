#pragma once
#include "Component.h"
#include "../Geometry/Vector3.h"
#include "../Geometry/Matrix4x4.h"

//Transform��������𼸺α任
class Transform : public Component
{
	friend class Mesh;
public:
	Transform();
	//����λ��
	void SetPosition(Vector3 pos);
	//��ȡλ��
	Vector3 GetPosition();
	//ƽ��
	void Translate(Vector3 delta);
	//��ת
	void Rotate(Vector3 angle);

private:
	//ģ�ͱ任����
	Matrix4x4 model;
	//λ��
	Vector3 position;
};
