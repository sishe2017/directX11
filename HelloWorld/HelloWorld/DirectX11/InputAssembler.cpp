#include "InputAssembler.h"
#include "../DirectX11.h"
#include "VertexShader.h"

using namespace Microsoft::WRL;
using namespace std;

//��һ��������������ݰ�����װ��׶�
void InputAssembler::BindVertexData()
{
	//������ɫ��δ����ֱ���׳��쳣
	if (!pVertexShader)
		throw "vertex not associate";

	//����������ݼ��ϳ�һά����
	vector<float> vertexData;
	for (int i = 0; i < vertexDatas.size(); i++)
		for (int j = 0; j < vertexDatas[i].size(); j++)
			vertexData.push_back(vertexDatas[i][j]);

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
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(float) * this->stride);
	//ÿ������Ĵ�С
	// todo:Ŀǰû����������Ե�����
	bufferDesc.StructureByteStride = 0;
	//���ó�������洢������
	D3D11_SUBRESOURCE_DATA sourceData;
	sourceData.pSysMem = vertexData.data();
	//��������λ�û������
	DirectX11::GetInstance().pDevice->CreateBuffer(&bufferDesc, &sourceData, &(buffer));

	//�������㲼��
	DirectX11::GetInstance().pDevice->CreateInputLayout(
		vertexDescs.data(), UINT(vertexDescs.size()), pVertexShader->pContent->GetBufferPointer(),
		pVertexShader->pContent->GetBufferSize(), &pInputLayout);
	//�󶨶���λ�ò���
	DirectX11::GetInstance().pContext->IASetInputLayout(this->pInputLayout.Get());
	//�󶨶��㻺��
	UINT offset = 0;
	DirectX11::GetInstance().pContext->IASetVertexBuffers(
		0, 1, buffer.GetAddressOf(), &stride, &offset);
	//�󶨶�����������
	DirectX11::GetInstance().pContext->IASetIndexBuffer(pIndex.Get(), DXGI_FORMAT_R32_UINT, 0);
	//����ͼԪװ���Ŀ��ͼԪ
	DirectX11::GetInstance().pContext->IASetPrimitiveTopology(this->basicPrimitive);
}

//���ö���λ������
void InputAssembler::SetVertexPos(std::vector<float> pos, UINT stride)
{
	//����λ����Ϣ����
	D3D11_INPUT_ELEMENT_DESC posDesc;
	//������ɫ���е�λ�õ���������
	posDesc.SemanticName = "POSITION";
	//�����������������к�����ͬ�������ʱ��������Ҫʹ������������������
	posDesc.SemanticIndex = 0;
	//��������ݵ�����
	posDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	//����۱��
	posDesc.InputSlot = 0;
	//��ȡ���ݵ���ʼλ��ƫ��
	posDesc.AlignedByteOffset = 0;
	//����������ݵ�����
	posDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	//ʵ�����Ƶĸ���
	posDesc.InstanceDataStepRate = 0;

	//��¼������������
	vertexDescs.push_back(posDesc);
	//��¼��������
	vertexDatas.push_back(pos);
	//��¼����
	this->stride += stride;
}

//���ö�����������
void InputAssembler::SetVertexTexCoord(std::vector<float> texCoords)
{
	//��������������Ϣ����
	D3D11_INPUT_ELEMENT_DESC textureDesc;
	//������ɫ���е������������������
	textureDesc.SemanticName = "TEXCOORD";
	//�����������������к�����ͬ�������ʱ��������Ҫʹ������������������
	textureDesc.SemanticIndex = 0;
	//��������ݵ�����
	textureDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
	//����۱�ţ�
	textureDesc.InputSlot = 0;
	//��ȡ���ݵ���ʼλ��ƫ��
	textureDesc.AlignedByteOffset = 0;
	//����������ݵ�����
	textureDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	//ʵ�����Ƶĸ���
	textureDesc.InstanceDataStepRate = 0;

	//��¼������������
	vertexDescs.push_back(textureDesc);
	//��¼��������
	vertexDatas.push_back(texCoords);
	//��¼����
	this->stride += 2;
}

//���ö�����������
void InputAssembler::SetVertexIndex(std::vector<unsigned int> &indices)
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
void InputAssembler::AssociateVertexShader(std::shared_ptr<VertexShader> pVertexShader)
{
	this->pVertexShader = pVertexShader;
}

//���ö�������
void InputAssembler::SetVertexData(std::vector<float> data, std::vector<unsigned int> strides, std::vector<std::string> semantics)
{
	//��¼ÿ����������
	for (int i = 0; i < strides.size(); i++)
	{
		//��¼���㲽��
		stride += strides[i];

		//��������������Ϣ
		D3D11_INPUT_ELEMENT_DESC desc;
		//������ɫ���е���������
		desc.SemanticName = semantics[i].c_str();
		//�����������������к�����ͬ�������ʱ��������Ҫʹ������������������
		desc.SemanticIndex = 0;
		//��������ݵ�����
		desc.Format = DXGI_FORMAT_R32G32_FLOAT;
		//����۱�ţ�
		desc.InputSlot = 0;
		//��ȡ���ݵ���ʼλ��ƫ��
		desc.AlignedByteOffset = 0;
		//����������ݵ�����
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		//ʵ�����Ƶĸ���
		desc.InstanceDataStepRate = 0;

		//��¼������������
		vertexDescs.push_back(desc);
	}
	//��¼��������
	vertexDatas.push_back(data);
}
