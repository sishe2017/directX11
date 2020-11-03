#include "Texture.h"
#include "DirectX11.h"
#include "DDSTextureLoader/DDSTextureLoader11.h"
#include "WICTextureLoader/WICTextureLoader11.h"

using namespace DirectX;

//根据路径加载图片
Texture::Texture(std::wstring path)
{
	//如果是dds类型的图片，则使用dds库加载图片
	if (path.rfind(L".dds") != std::wstring::npos)
	{
		//创建纹理资源和纹理资源视图
		DirectX::CreateDDSTextureFromFile(
			DirectX11::GetInstance().pDevice.Get(),
			path.c_str(),
			this->pTexture.GetAddressOf(),
			&this->pTextureView
		);
	}
	//否则使用WIC库加载图片
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

//绑定纹理
void Texture::Bind()
{
	DirectX11::GetInstance().pContext->PSSetShaderResources(0, 1, this->pTextureView.GetAddressOf());
}
