#pragma once
#include <vector>
#include "../Type.h"
#include <wrl.h>
#include <d3d11.h>
#include <string>
#include <memory>

class VertexShader;

class InputAssembler
{
	friend class DirectX11;
	friend class DirectX11Pipeline;

	//��������
	struct VertexData
	{
		//�������ݻ���
		Microsoft::WRL::ComPtr<ID3D11Buffer> pVertex;
		//������һ����������Գ���
		UINT stride = 0;
		//���濪ʼ��ȡ��λ��ƫ��
		UINT offset = 0;
	};
public:
	//���û��ƵĻ���ͼԪ
	void SetPrimitive(BasicPrimitive basicPrimitive);
	//����������ɫ��
	void AssociateVertexShader(std::shared_ptr<VertexShader> pVertexShader);
	//���ö���λ������
	void SetVertexPos(std::vector<float> positions, UINT stride = 3 * sizeof(float), UINT offset = 0);
	//���ö�����������
	void SetVertexIndex(std::vector<unsigned int> indices);
	//������װ��׶�
	void Bind();

private:
	//����ͼԪĬ����������
	D3D11_PRIMITIVE_TOPOLOGY basicPrimitive = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	//����λ������
	VertexData vertexPosition;
	//����λ�õĲ���
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	//������������
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndex;
	//�������Լ���
	std::vector<D3D11_INPUT_ELEMENT_DESC> vertexProperties;
	//�����Ķ�����ɫ��
	std::shared_ptr<VertexShader> pVertexShader;
	//��������
	std::vector<unsigned int> indices;
};
