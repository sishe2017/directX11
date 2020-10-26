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

//像素着色器
class PixelShader 
{
public:
	PixelShader(std::wstring path);
	//绑定像素着色器
	void Bind();
	//设置像素着色器中的常量
	void SetConstant(ConstantBuffer constantBuffer, unsigned int index);
	//加载纹理
	void LoadTexture(std::shared_ptr<Texture> texture);

private:
	//常量集合
	std::vector<ConstantBuffer> datas;
	//DirectX11像素着色器
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	//顶点着色器内容
	Microsoft::WRL::ComPtr<ID3DBlob> pContent;
	//采样器集合
	std::vector<std::shared_ptr<Sampler>> samplers;
	//纹理集合
	std::vector<std::shared_ptr<Texture>> textures;
};
