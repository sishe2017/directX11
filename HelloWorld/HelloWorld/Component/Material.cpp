#include "Material.h"
#include "../DirectX11Pipeline.h"
#include "../ShaderTable.h"
#include "../TextureTable.h"

using namespace std;

Material::Material()
{
}

//加载像素着色器
void Material::LoadPixelShader(std::wstring shaderName)
{
	this->pixelShader = ShaderTable::GetPixelShader(shaderName);
}

//设置颜色
void Material::SetColor(float red, float green, float blue, float alpha)
{
	
}

//绘制材质
void Material::Draw()
{
	//将像素着器绑定至流水线中
	DirectX11Pipeline::BindPixelShader(pixelShader);
}

//加载纹理
void Material::LoadTexture(std::wstring path)
{
	this->texture = TextureTable::GetTexture(path);
}
