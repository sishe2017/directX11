#pragma once
#include <wrl.h>
#include <d3d11.h>


//������
class Sampler
{
	friend class PixelShader;
public:
	Sampler();
	//�󶨲�����
	void Bind();

private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;
};

