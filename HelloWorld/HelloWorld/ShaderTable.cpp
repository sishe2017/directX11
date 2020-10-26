#include "ShaderTable.h"

using namespace std;

std::shared_ptr<VertexShader> ShaderTable::GetVertexShader(std::wstring shaderName)
{
	//ƴ��shader��·��
	auto path = wstring(L"Shader/") + shaderName + wstring(L".cso");
	return GetInstance().vertexShaderTable[path];
}

std::shared_ptr<PixelShader> ShaderTable::GetPixelShader(std::wstring shaderName)
{
	//ƴ��shader��·��
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

//��ʼ��Shader��
void ShaderTable::Init()
{
	//��ʼ��������ɫ��
	vertexShaderTable[L"Shader/CubeVS.cso"] = make_shared<VertexShader>(L"Shader/CubeVS.cso");
	
	//��ʼ��������ɫ��
	pixelShaderTable[L"Shader/CubePS.cso"] = make_shared<PixelShader>(L"Shader/CubePS.cso");
}
