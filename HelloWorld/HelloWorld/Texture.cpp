#include "Texture.h"
#include "DirectX11.h"
#include "DDSTextureLoader/DDSTextureLoader11.h"
#include "WICTextureLoader/WICTextureLoader11.h"

using namespace DirectX;

//����·������ͼƬ
Texture::Texture(std::wstring path)
{
	//�����dds���͵�ͼƬ����ʹ��dds�����ͼƬ
	if (path.rfind(L".dds") != std::wstring::npos)
	{
		//����������Դ��������Դ��ͼ
		DirectX::CreateDDSTextureFromFile(
			DirectX11::GetInstance().pDevice.Get(),
			path.c_str(),
			this->pTexture.GetAddressOf(),
			&this->pTextureView
		);
	}
	//����ʹ��WIC�����ͼƬ
	else
	{
		DirectX::CreateWICTextureFromFile(
			DirectX11::GetInstance().pDevice.Get(),
			path.c_str(),
			this->pTexture.GetAddressOf(),
			&this->pTextureView
		);
	}
}

//������
void Texture::Bind()
{
	DirectX11::GetInstance().pContext->PSSetShaderResources(0, 1, this->pTextureView.GetAddressOf());
}
