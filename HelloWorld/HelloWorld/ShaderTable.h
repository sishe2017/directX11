#pragma once
#include "DirectX11/VertexShader.h"
#include "DirectX11/PixelShader.h"
#include <memory>
#include <string>
#include <map>

//��ɫ����
class ShaderTable
{
public:
	//����·������ȡ������ɫ��
	static std::shared_ptr<VertexShader> GetVertexShader(std::wstring shaderName);
	//����·������ȡ������ɫ��
	static std::shared_ptr<PixelShader> GetPixelShader(std::wstring shaderName);

private:
	//����ģʽ
	ShaderTable();
	ShaderTable(const ShaderTable&) = delete;
	ShaderTable& operator=(const ShaderTable&) = delete;
	static ShaderTable& GetInstance();
	//��ʼ��Shader��
	void Init();
	//������ɫ����
	std::map<std::wstring, std::shared_ptr<VertexShader>> vertexShaderTable;
	//������ɫ����
	std::map<std::wstring, std::shared_ptr<PixelShader>> pixelShaderTable;
};

