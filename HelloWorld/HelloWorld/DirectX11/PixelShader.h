#pragma once
#include <string>
#include "ConstantBuffer.h"
#include <wrl.h>
#include <d3d11.h>
#include <vector>


class PixelShader 
{
public:
	//����������ɫ��
	void Load(std::wstring path);
	//��������ɫ��
	void Bind();
	//����������ɫ���еĳ���
	void SetConstant(ConstantBuffer constantBuffer, unsigned int index);

private:
	//��������
	std::vector<ConstantBuffer> datas;
	//DirectX11������ɫ��
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	//������ɫ������
	Microsoft::WRL::ComPtr<ID3DBlob> pContent;
};
