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
	//���ó���������������Ϣ
	D3D11_BUFFER_DESC bufferDesc = {};
	//������������shader����ĳ���
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//��������ֻ����CPUд�룬GPU����
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	//CPU���Է�������
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	//�������ĳ���4��4���󳤶�
	bufferDesc.ByteWidth = sizeof(float) * 4 * 4;
	bufferDesc.StructureByteStride = 0;
	//���ó�������洢������
	D3D11_SUBRESOURCE_DATA sourceData;
	sourceData.pSysMem = &(matrix.matrix);
	//��������������
	DirectX11::GetInstance().pDevice->CreateBuffer(&bufferDesc, &sourceData, &pBuffer);
}

ConstantBuffer::ConstantBuffer(std::vector<float> arr)
{
	//���ó���������������Ϣ
	D3D11_BUFFER_DESC bufferDesc = {};
	//������������shader����ĳ���
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//��������ֻ����CPUд�룬GPU����
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	//CPU���Է�������
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	//�������ĳ���4��4���󳤶�
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(float) * arr.size());
	bufferDesc.StructureByteStride = 0;
	//���ó�������洢������
	D3D11_SUBRESOURCE_DATA sourceData;
	sourceData.pSysMem = arr.data();
	//��������������
	DirectX11::GetInstance().pDevice->CreateBuffer(&bufferDesc, &sourceData, &pBuffer);
}
