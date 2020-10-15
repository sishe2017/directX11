#pragma once
#include <string>
#include "ConstantBuffer.h"
#include <wrl.h>
#include <d3d11.h>
#include <vector>


class PixelShader 
{
public:
	//加载像素着色器
	void Load(std::wstring path);
	//绑定像素着色器
	void Bind();
	//设置像素着色器中的常量
	void SetConstant(ConstantBuffer constantBuffer, unsigned int index);

private:
	//常量集合
	std::vector<ConstantBuffer> datas;
	//DirectX11像素着色器
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	//顶点着色器内容
	Microsoft::WRL::ComPtr<ID3DBlob> pContent;
};
