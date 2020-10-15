#pragma once
#include "Component.h"
#include <string>
#include <memory>
#include "../DirectX11/PixelShader.h"

class Material : public Component
{
public:
	Material();

	//����������ɫ��
	void LoadPixelShader(std::wstring path);
	//������ɫ
	void SetColor(float red, float green, float blue, float alpha);
	//���Ʋ���
	void Draw();

//private:
	//��Ϸ�����������ɫ��
	std::shared_ptr<PixelShader> pixelShader;
};

