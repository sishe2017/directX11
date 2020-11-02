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

public:
	//���û��ƵĻ���ͼԪ
	void SetPrimitive(BasicPrimitive basicPrimitive);
	//����������ɫ��
	void AssociateVertexShader(std::shared_ptr<VertexShader> pVertexShader);
	//���ö�����������
	void SetVertexData(std::vector<float> data, std::vector<unsigned int> strides, std::vector<std::string> semantics);
	//���ö���λ������
	void SetVertexPos(std::vector<float> positions, UINT stride = 3 * sizeof(float));
	//���ö�����������
	void SetVertexTexCoord(std::vector<float> texCoords);
	//���ö�����������
	void SetVertexIndex(std::vector<unsigned int> &indices);
	//�Ѷ�������ݰ�����װ��׶�
	void BindVertexData();

private:
	//����ͼԪĬ����������
	D3D11_PRIMITIVE_TOPOLOGY basicPrimitive = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	//����λ�õĲ���
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	//������������
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndex;
	//����������������
	std::vector<D3D11_INPUT_ELEMENT_DESC> vertexDescs;
	//�������ݼ���
	std::vector<std::vector<float>> vertexDatas;
	//�����Ķ�����ɫ��
	std::shared_ptr<VertexShader> pVertexShader;
	//��������
	std::vector<unsigned int> indices;
	//���ݲ�������
	std::vector<unsigned int> strides;
	//dx11 buffer
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;

	//��ȡ�������еĲ���
	unsigned int GetCurrentStride();
};
