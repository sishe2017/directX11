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

	//����������ɫ��
	void LoadPixelShader(std::wstring shaderName);
	//������ɫ
	void SetColor(float red, float green, float blue, float alpha);
	//���Ʋ���
	void Draw();
	//��������
	void LoadTexture(std::wstring path);


	//��Ϸ�����������ɫ��
	std::shared_ptr<PixelShader> pixelShader;
private:
	//����
	std::shared_ptr<Texture> texture;
};

