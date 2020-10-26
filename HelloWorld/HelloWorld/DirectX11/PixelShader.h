#pragma once
#include <string>
#include "ConstantBuffer.h"
#include <wrl.h>
#include <d3d11.h>
#include <vector>
#include <memory>
#include <vector>

class Texture;
class Sampler;

//������ɫ��
class PixelShader 
{
public:
	PixelShader(std::wstring path);
	//��������ɫ��
	void Bind();
	//����������ɫ���еĳ���
	void SetConstant(ConstantBuffer constantBuffer, unsigned int index);
	//��������
	void LoadTexture(std::shared_ptr<Texture> texture);

private:
	//��������
	std::vector<ConstantBuffer> datas;
	//DirectX11������ɫ��
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	//������ɫ������
	Microsoft::WRL::ComPtr<ID3DBlob> pContent;
	//����������
	std::vector<std::shared_ptr<Sampler>> samplers;
	//������
	std::vector<std::shared_ptr<Texture>> textures;
};
