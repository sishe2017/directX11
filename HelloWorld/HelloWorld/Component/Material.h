#pragma once
#include "Component.h"
#include <string>
#include <memory>
#include "../DirectX11/PixelShader.h"

class Texture;

class Material : public Component
{
public:
	Material();

	//加载像素着色器
	void LoadPixelShader(std::wstring shaderName);
	//设置颜色
	void SetColor(float red, float green, float blue, float alpha);
	//绘制材质
	void Draw();
	//加载纹理
	void LoadTexture(std::wstring path);


	//游戏物体的像素着色器
	std::shared_ptr<PixelShader> pixelShader;
private:
	//纹理
	std::shared_ptr<Texture> texture;
};

