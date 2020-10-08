#pragma once
#include "Matrix4x4.h"
#include "ConstantBuffer.h"
#include <vector>
#include <wrl.h>
#include <d3d11.h>
#include <string>


class VertexShader
{
public:
	//���ض�����ɫ��
	void Load(std::wstring path);
	//�󶨶�����ɫ��
	void Bind();
	//���ö�����ɫ���еĳ���
	void SetConstant(ConstantBuffer constantBuffer, unsigned int index);

private:
	//��������
	std::vector<ConstantBuffer> datas;
	//DirectX11������ɫ��
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	//������ɫ������
	Microsoft::WRL::ComPtr<ID3DBlob> pContent;
};
