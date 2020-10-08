#include "ConstantBuffer.h"
#include "DirectX11.h"

ConstantBuffer::ConstantBuffer(float val)
{
}

ConstantBuffer::ConstantBuffer(Vector2 vector2)
{
}

ConstantBuffer::ConstantBuffer(Vector3 vector3)
{
}

ConstantBuffer::ConstantBuffer(Matrix4x4 matrix)
{
	//设置常量缓冲区描述信息
	D3D11_BUFFER_DESC bufferDesc = {};
	//缓冲区的用于shader程序的常量
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//缓存数据只能由CPU写入，GPU读出
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	//CPU可以访问数据
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	//缓冲区的长度4×4矩阵长度
	bufferDesc.ByteWidth = sizeof(float) * 4 * 4;
	bufferDesc.StructureByteStride = 0;
	//设置常量缓存存储的数据
	D3D11_SUBRESOURCE_DATA sourceData;
	sourceData.pSysMem = &(matrix.matrix);
	//创建常量缓冲区
	DirectX11::GetInstance().pDevice->CreateBuffer(&bufferDesc, &sourceData, &pBuffer);
}

ConstantBuffer::ConstantBuffer(std::vector<float> arr)
{
	//设置常量缓冲区描述信息
	D3D11_BUFFER_DESC bufferDesc = {};
	//缓冲区的用于shader程序的常量
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//缓存数据只能由CPU写入，GPU读出
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	//CPU可以访问数据
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	//缓冲区的长度4×4矩阵长度
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(float) * arr.size());
	bufferDesc.StructureByteStride = 0;
	//设置常量缓存存储的数据
	D3D11_SUBRESOURCE_DATA sourceData;
	sourceData.pSysMem = arr.data();
	//创建常量缓冲区
	DirectX11::GetInstance().pDevice->CreateBuffer(&bufferDesc, &sourceData, &pBuffer);
}
