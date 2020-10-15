#pragma once
#include <DirectXMath.h>
#include "Vector3.h"

	
//4��4����
class Matrix4x4
{
	friend Matrix4x4 operator*(Matrix4x4 m1, Matrix4x4 m2);
	friend class DirectX11;
	friend class ConstantBuffer;

public:
	
	Matrix4x4();

	Matrix4x4& operator*=(Matrix4x4 matrix);
	//����һ��ƽ�ƾ���
	static Matrix4x4 Translation(Vector3 vector3);
	//����һ����ת����
	static Matrix4x4 Rotation(Vector3 vector3);
	//����һ�����ž���
	static Matrix4x4 Scale(Vector3 vector3);
	//����һ��ת�þ���
	static Matrix4x4 Transpose(Matrix4x4 matrix);
	//����һ��͸�Ӿ���
	static Matrix4x4 Perspective(float viewWidth, float viewHeight, float nearZ, float farZ);
	
private:
	Matrix4x4(DirectX::XMMATRIX matrix);
	DirectX::XMMATRIX matrix;
};



