#pragma once
#include "Texture.h"
#include <memory>
#include <string>
#include <map>


class TextureTable
{
public:
	//����·������ȡ�������
	static std::shared_ptr<Texture> GetTexture(std::wstring path);

private:
	//����ģʽ
	TextureTable();
	TextureTable(const TextureTable&) = delete;
	TextureTable& operator=(const TextureTable&) = delete;
	static TextureTable& GetInstance();

	//��ʼ�������
	void Init();
	//�����
	std::map<std::wstring, std::shared_ptr<Texture>> textureTable;
};

