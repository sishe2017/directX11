#pragma once
#include <wrl.h>
#include <d3d11.h>


//采样器
class Sampler
{
	friend class PixelShader;
public:
	Sampler();
	//绑定采样器
	void Bind();

private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;
};

