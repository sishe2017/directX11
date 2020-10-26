#include "TextureTable.h"

using namespace std;

TextureTable& TextureTable::GetInstance()
{
    static TextureTable textureTable;
    return textureTable;
}

//根据路径名获取纹理对象
std::shared_ptr<Texture> TextureTable::GetTexture(std::wstring path)
{
    return GetInstance().textureTable[path];
}

TextureTable::TextureTable()
{
    Init();
}

//初始化纹理表
void TextureTable::Init()
{
    //初始化纹理表
    textureTable[L"Images/kappa50.png"] = std::make_shared<Texture>(L"Images/kappa50.png");
}
