#include "Sampler.h"
#include "DirectX11.h"

Sampler::Sampler()
{
	//采样器描述信息
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	//创建directX11采样器
	DirectX11::GetInstance().pDevice->CreateSamplerState(&samplerDesc, &pSampler);
}

//绑定采样器
void Sampler::Bind()
{
	//绑定DirectX11采样器
	DirectX11::GetInstance().pContext->PSSetSamplers(0, 1, pSampler.GetAddressOf());
}
