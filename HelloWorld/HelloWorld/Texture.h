#pragma once
#include "DDSTextureLoader/DDSTextureLoader11.h"
#include <string>
#include <d3d11.h>
#include <wrl.h>

//纹理
class Texture
{
	friend class PixelShader;
public:
	//根据路径加载图片
	Texture(std::wstring path);
	//绑定纹理
	void Bind();
private:
	//资源接口
	Microsoft::WRL::ComPtr<ID3D11Resource> pTexture;
	//资源视图
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
};
