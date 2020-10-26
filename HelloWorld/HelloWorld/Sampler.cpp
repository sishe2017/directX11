#include "Sampler.h"
#include "DirectX11.h"

Sampler::Sampler()
{
	//������������Ϣ
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	//����directX11������
	DirectX11::GetInstance().pDevice->CreateSamplerState(&samplerDesc, &pSampler);
}

//�󶨲�����
void Sampler::Bind()
{
	//��DirectX11������
	DirectX11::GetInstance().pContext->PSSetSamplers(0, 1, pSampler.GetAddressOf());
}
