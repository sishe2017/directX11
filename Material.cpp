#include "Material.h"
#include "DirectX11Pipeline.h"

using namespace std;

Material::Material()
{
	//���ʵ�������ɫ��
	pixelShader = make_shared<PixelShader>();
}

//����������ɫ��
void Material::LoadPixelShader(std::wstring path)
{
	pixelShader->Load(path);
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
