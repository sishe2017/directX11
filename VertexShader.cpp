#include "VertexShader.h"
#include <d3dcompiler.h>
#include "DirectX11.h"

//加载顶点着色器
void VertexShader::Load(std::wstring path)
{
	D3DReadFileToBlob(path.c_str(), &pContent);
	DirectX11::GetInstance().pDevice->CreateVertexShader(
		pContent->GetBufferPointer(), pContent->GetBufferSize(),
		nullptr, &pVertexShader
	);
}

//绑定顶点着色器
void VertexShader::Bind()
{
	//绑定顶点着色器
	DirectX11::GetInstance().pContext->VSSetShader(pVertexShader.Get(), nullptr, 0);
	//绑定常量
	for (int i = 0; i < datas.size(); i++)
		DirectX11::GetInstance().pContext->VSSetConstantBuffers(0, 1, datas[i].pBuffer.GetAddressOf());
}

//设置顶点着色器中的常量
void VertexShader::SetConstant(ConstantBuffer constantBuffer, unsigned int index)
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