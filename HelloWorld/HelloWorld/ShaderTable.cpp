#include "ShaderTable.h"

using namespace std;

std::shared_ptr<VertexShader> ShaderTable::GetVertexShader(std::wstring shaderName)
{
	//拼接shader的路径
	auto path = wstring(L"Shader/") + shaderName + wstring(L".cso");
	return GetInstance().vertexShaderTable[path];
}

std::shared_ptr<PixelShader> ShaderTable::GetPixelShader(std::wstring shaderName)
{
	//拼接shader的路径
	auto path = wstring(L"Shader/") + shaderName + wstring(L".cso");
	return GetInstance().pixelShaderTable[path];
}

ShaderTable::ShaderTable()
{
	Init();
}

ShaderTable& ShaderTable::GetInstance()
{
	static ShaderTable shaderTable;
	return shaderTable;
}

//初始化Shader表
void ShaderTable::Init()
{
	//初始化顶点着色器
	vertexShaderTable[L"Shader/CubeVS.cso"] = make_shared<VertexShader>(L"Shader/CubeVS.cso");
	
	//初始化像素着色器
	pixelShaderTable[L"Shader/CubePS.cso"] = make_shared<PixelShader>(L"Shader/CubePS.cso");
}
