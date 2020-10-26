#pragma once
#include "DDSTextureLoader/DDSTextureLoader11.h"
#include <string>
#include <d3d11.h>
#include <wrl.h>

//����
class Texture
{
	friend class PixelShader;
public:
	//����·������ͼƬ
	Texture(std::wstring path);
	//������
	void Bind();
private:
	//��Դ�ӿ�
	Microsoft::WRL::ComPtr<ID3D11Resource> pTexture;
	//��Դ��ͼ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
};
