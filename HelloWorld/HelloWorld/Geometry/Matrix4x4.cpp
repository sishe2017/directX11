#include "Matrix4x4.h"

using namespace DirectX;

//默认构造函数生成单位矩阵
Matrix4x4::Matrix4x4()
{
	matrix = XMMatrixIdentity();
}

Matrix4x4& Matrix4x4::operator*=(Matrix4x4 matrix)
{
	this->matrix *= matrix.matrix;
	return *this;
}

//默认构造函数生成单位矩阵
Matrix4x4::Matrix4x4(XMMATRIX matrix):
	matrix(matrix)
{
}

//生成一个平移矩阵
Matrix4x4 Matrix4x4::Translation(Vector3 vector3)
{
	return Matrix4x4(XMMatrixTranslation(vector3.x, vector3.y, vector3.z));
}

//生成一个旋转矩阵
Matrix4x4 Matrix4x4::Rotation(Vector3 vector3)
{
	return Matrix4x4(XMMatrixRotationRollPitchYaw(vector3.x, vector3.y, vector3.z));
}

//生成一个缩放矩阵
Matrix4x4 Matrix4x4::Scale(Vector3 vector3)
{
	return Matrix4x4(XMMatrixScaling(vector3.x, vector3.y, vector3.z));
}

//生成一个转置矩阵
Matrix4x4 Matrix4x4::Transpose(Matrix4x4 matrix)
{
	return Matrix4x4(XMMatrixTranspose(matrix.matrix));
}

//生成一个透视矩阵
Matrix4x4 Matrix4x4::Perspective(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	//return Matrix4x4(XMMatrixPerspectiveRH(viewWidth, viewHeight, nearZ, farZ));
	return Matrix4x4(XMMatrixPerspectiveLH(viewWidth, viewHeight, nearZ, farZ));
}

//矩阵乘法
Matrix4x4 operator*(Matrix4x4 m1, Matrix4x4 m2)
{
	return Matrix4x4(m1.matrix * m2.matrix);
}