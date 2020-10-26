#pragma once
#include "DirectX11/VertexShader.h"
#include "DirectX11/PixelShader.h"
#include <memory>
#include <string>
#include <map>

//着色器表
class ShaderTable
{
public:
	//根据路径名获取顶点着色器
	static std::shared_ptr<VertexShader> GetVertexShader(std::wstring shaderName);
	//根据路径名获取像素着色器
	static std::shared_ptr<PixelShader> GetPixelShader(std::wstring shaderName);

private:
	//单例模式
	ShaderTable();
	ShaderTable(const ShaderTable&) = delete;
	ShaderTable& operator=(const ShaderTable&) = delete;
	static ShaderTable& GetInstance();
	//初始化Shader表
	void Init();
	//顶点着色器表
	std::map<std::wstring, std::shared_ptr<VertexShader>> vertexShaderTable;
	//像素着色器表
	std::map<std::wstring, std::shared_ptr<PixelShader>> pixelShaderTable;
};

