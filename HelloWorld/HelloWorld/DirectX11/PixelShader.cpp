#include "PixelShader.h"
#include <d3dcompiler.h>
#include "../DirectX11.h"
#include "../Texture.h"
#include "../Sampler.h"

using namespace std;

//加载像素着色器
PixelShader::PixelShader(std::wstring path)
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
	//纹理集合中有纹理对象，绑定纹理和采样器
	if (!textures.empty())
	{
		for (int i = 0; i < textures.size(); i++)
		{
			textures[i]->Bind();
			samplers[i]->Bind();
		}
	}
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

	//绑定常量
	for (int i = 0; i < datas.size(); i++)
		DirectX11::GetInstance().pContext->PSSetConstantBuffers(0, 1, datas[i].pBuffer.GetAddressOf());
}

//设置纹理
void PixelShader::LoadTexture(std::shared_ptr<Texture> texture)
{
	textures.push_back(texture);
	//有新的纹理加载进来的时候，生成一个采样器
	auto sampler = make_shared<Sampler>();
	//记录对应生成的采样器
	samplers.push_back(sampler);
}
