#include "InputAssembler.h"
#include "DirectX11.h"

using namespace Microsoft::WRL;

//������װ��׶�
void InputAssembler::Bind()
{
	//������ɫ��δ����ֱ���׳��쳣
	if (!pVertexShader)
		throw "vertex not associate";
	//�������㲼��
	DirectX11::GetInstance().pDevice->CreateInputLayout(
		vertexProperties.data(), UINT(vertexProperties.size()), pVertexShader->GetBufferPointer(),
		pVertexShader->GetBufferSize(), &pInputLayout);
	//�󶨶���λ�ò���
	DirectX11::GetInstance().pContext->IASetInputLayout(this->pInputLayout.Get());
	//�󶨶��㻺��
	DirectX11::GetInstance().pContext->IASetVertexBuffers(
		0, 1, vertexPosition.pVertex.GetAddressOf(), &(vertexPosition.stride), &(vertexPosition.offset));
	//�󶨶�����������
	DirectX11::GetInstance().pContext->IASetIndexBuffer(pIndex.Get(), DXGI_FORMAT_R32_UINT, 0);
	//����ͼԪװ���Ŀ��ͼԪ
	DirectX11::GetInstance().pContext->IASetPrimitiveTopology(this->basicPrimitive);
}

//���ö���λ������
void InputAssembler::SetVertexPos(std::vector<float> vertices, UINT stride, UINT offset)
{
	//���ö���λ�õĲ�����ƫ��
	vertexPosition.stride = stride;
	vertexPosition.offset = offset;
	//����������Ϣ
	D3D11_BUFFER_DESC bufferDesc;
	//��־�������ڶ��㻺��
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//��;��Ĭ����;��GPU���Զ�д��Ƭ����
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//CPU���ɷ�����Ƭ�ڴ�
	bufferDesc.CPUAccessFlags = 0;
	//���������������־
	bufferDesc.MiscFlags = 0;
	//����Ĵ�С�����ֽ�Ϊ��λ
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(float) * vertices.size());
	//ÿ������Ĵ�С
	// todo:Ŀǰû����������Ե�����
	bufferDesc.StructureByteStride = 0;
	//���ó�������洢������
	D3D11_SUBRESOURCE_DATA sourceData;
	sourceData.pSysMem = vertices.data();
	//��������λ�û������
	DirectX11::GetInstance().pDevice->CreateBuffer(&bufferDesc, &sourceData, &(vertexPosition.pVertex));

	//����λ����Ϣ����
	D3D11_INPUT_ELEMENT_DESC posDesc;
	//������ɫ���е�λ�õ���������
	posDesc.SemanticName = "POSITION";
	//�����������������к�����ͬ�������ʱ��������Ҫʹ������������������
	posDesc.SemanticIndex = 0;
	//��������ݵ�����
	posDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	//����۱�ţ�
	posDesc.InputSlot = 0;
	//��ȡ���ݵ���ʼλ��ƫ��
	posDesc.AlignedByteOffset = 0;
	//����������ݵ�����
	posDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	//ʵ�����Ƶĸ���
	posDesc.InstanceDataStepRate = 0;

	//��¼������������
	vertexProperties.push_back(posDesc);
}

//���ö�����������
void InputAssembler::SetVertexIndex(std::vector<unsigned int> indices)
{
	//��¼��������
	this->indices = indices;

	//����������Ϣ
	D3D11_BUFFER_DESC bufferDesc;
	//��־�������ڶ�������
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//��;��Ĭ����;��GPU���Զ�д��Ƭ����
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//CPU���ɷ�����Ƭ�ڴ�
	bufferDesc.CPUAccessFlags = 0;
	//���������������־
	bufferDesc.MiscFlags = 0;
	//����Ĵ�С�����ֽ�Ϊ��λ
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(unsigned int) * indices.size());
	//ÿ������Ĵ�С
	bufferDesc.StructureByteStride = 0;
	//������������ʵ����Ϣ
	D3D11_SUBRESOURCE_DATA sourceData;
	sourceData.pSysMem = this->indices.data();
	//����������������
	DirectX11::GetInstance().pDevice->CreateBuffer(&bufferDesc, &sourceData, &pIndex);
}

//���û��ƵĻ���ͼԪ
void InputAssembler::SetPrimitive(BasicPrimitive basicPrimitive)
{
	//������ͼԪ
	if (basicPrimitive == BasicPrimitive::Triangle)
		this->basicPrimitive = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

//����������ɫ��
void InputAssembler::AssociateVertexShader(std::wstring path)
{
	D3DReadFileToBlob(L"VertexShader.cso", &pVertexShader);
}
