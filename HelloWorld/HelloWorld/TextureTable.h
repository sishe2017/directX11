#pragma once
#include "Texture.h"
#include <memory>
#include <string>
#include <map>


class TextureTable
{
public:
	//根据路径名获取纹理对象
	static std::shared_ptr<Texture> GetTexture(std::wstring path);

private:
	//单例模式
	TextureTable();
	TextureTable(const TextureTable&) = delete;
	TextureTable& operator=(const TextureTable&) = delete;
	static TextureTable& GetInstance();

	//初始化纹理表
	void Init();
	//纹理表
	std::map<std::wstring, std::shared_ptr<Texture>> textureTable;
};

