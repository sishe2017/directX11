#include "PixelShader.h"
#include <d3dcompiler.h>
#include "../DirectX11.h"

//加载像素着色器
void PixelShader::Load(std::wstring path)
{
	D3DReadFileToBlob(path.c_str(), &pContent);
	DirectX11::GetInstance().pDevice->CreatePixelShader(
		pContent->GetBufferPointer(), pContent->GetBufferSize(),
		nullptr, &pPixelShader
	);
}

//绑定像素着色器
void PixelShader::Bind()
{
	//绑定顶点着色器
	DirectX11::GetInstance().pContext->PSSetShader(pPixelShader.Get(), nullptr, 0);
	//绑定常量
	for (int i = 0; i < datas.size(); i++)
		DirectX11::GetInstance().pContext->PSSetConstantBuffers(0, 1, datas[i].pBuffer.GetAddressOf());
}

//设置像素着色器中的常量
void PixelShader::SetConstant(ConstantBuffer constantBuffer, unsigned int index)
{
	//必须按照shader的变量顺序进行赋值
	if (index > datas.size())
		throw "set constant variable out of order";
	//记录新的常量
	else if (index == datas.size())
		datas.push_back(constantBuffer);
	//改变常量
	else
		datas[index] = constantBuffer;
}