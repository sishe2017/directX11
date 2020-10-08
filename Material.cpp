#include "Material.h"
#include "DirectX11Pipeline.h"

using namespace std;

Material::Material()
{
	//材质的像素着色器
	pixelShader = make_shared<PixelShader>();
}

//加载像素着色器
void Material::LoadPixelShader(std::wstring path)
{
	pixelShader->Load(path);
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
