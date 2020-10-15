#pragma once
#include <DirectXMath.h>
#include "Vector3.h"

	
//4×4矩阵
class Matrix4x4
{
	friend Matrix4x4 operator*(Matrix4x4 m1, Matrix4x4 m2);
	friend class DirectX11;
	friend class ConstantBuffer;

public:
	
	Matrix4x4();

	Matrix4x4& operator*=(Matrix4x4 matrix);
	//生成一个平移矩阵
	static Matrix4x4 Translation(Vector3 vector3);
	//生成一个旋转矩阵
	static Matrix4x4 Rotation(Vector3 vector3);
	//生成一个缩放矩阵
	static Matrix4x4 Scale(Vector3 vector3);
	//生成一个转置矩阵
	static Matrix4x4 Transpose(Matrix4x4 matrix);
	//生成一个透视矩阵
	static Matrix4x4 Perspective(float viewWidth, float viewHeight, float nearZ, float farZ);
	
private:
	Matrix4x4(DirectX::XMMATRIX matrix);
	DirectX::XMMATRIX matrix;
};



