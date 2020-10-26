#include "TextureTable.h"

using namespace std;

TextureTable& TextureTable::GetInstance()
{
    static TextureTable textureTable;
    return textureTable;
}

//����·������ȡ�������
std::shared_ptr<Texture> TextureTable::GetTexture(std::wstring path)
{
    return GetInstance().textureTable[path];
}

TextureTable::TextureTable()
{
    Init();
}

//��ʼ�������
void TextureTable::Init()
{
    //��ʼ�������
    textureTable[L"Images/kappa50.png"] = std::make_shared<Texture>(L"Images/kappa50.png");
}
