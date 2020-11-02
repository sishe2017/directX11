#include "Material.h"
#include "../DirectX11Pipeline.h"
#include "../ShaderTable.h"
#include "../TextureTable.h"

using namespace std;

Material::Material()
{
}

//����������ɫ��
void Material::LoadPixelShader(std::wstring shaderName)
{
	this->pixelShader = ShaderTable::GetPixelShader(shaderName);
}

//������ɫ
void Material::SetColor(float red, float green, float blue, float alpha)
{
	
}

//���Ʋ���
void Material::Draw()
{
	//����������������ˮ����
	DirectX11Pipeline::BindPixelShader(pixelShader);
}

//��������
void Material::LoadTexture(std::wstring path)
{
	auto pTexture = TextureTable::GetTexture(path);
	//��������ж�ȡ����
	this->textures.push_back(pTexture);
	//������ɫ����������
	this->pixelShader->LoadTexture(pTexture);
}
