#include "Texture.h"
#include "DirectX11.h"

using namespace DirectX;

//根据路径加载图片
Texture::Texture(std::wstring path)
{
	//创建纹理资源和纹理资源视图
	DirectX::CreateDDSTextureFromFile(
		DirectX11::GetInstance().pDevice.Get(),
		path.c_str(),
		this->pTexture.GetAddressOf(),
		this->pTextureView.GetAddressOf()
	);
}

//绑定纹理
void Texture::Bind()
{
	DirectX11::GetInstance().pContext->PSGetShaderResources(0, 1, this->pTextureView.GetAddressOf());
}
