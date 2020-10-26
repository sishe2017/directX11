#include "Texture.h"
#include "DirectX11.h"

using namespace DirectX;

//����·������ͼƬ
Texture::Texture(std::wstring path)
{
	//����������Դ��������Դ��ͼ
	DirectX::CreateDDSTextureFromFile(
		DirectX11::GetInstance().pDevice.Get(),
		path.c_str(),
		this->pTexture.GetAddressOf(),
		this->pTextureView.GetAddressOf()
	);
}

//������
void Texture::Bind()
{
	DirectX11::GetInstance().pContext->PSGetShaderResources(0, 1, this->pTextureView.GetAddressOf());
}
