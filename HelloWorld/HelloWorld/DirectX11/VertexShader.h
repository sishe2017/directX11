#pragma once
#include "../Geometry/Matrix4x4.h"
#include "ConstantBuffer.h"
#include <vector>
#include <wrl.h>
#include <d3d11.h>
#include <string>

//顶点着色器
class VertexShader
{
	friend class InputAssembler;
public:
	VertexShader(std::wstring path);
	//绑定顶点着色器
	void Bind();
	//设置顶点着色器中的常量
	void SetConstant(ConstantBuffer constantBuffer, unsigned int index);

private:
	//常量集合
	std::vector<ConstantBuffer> datas;
	//DirectX11顶点着色器
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	//顶点着色器内容
	Microsoft::WRL::ComPtr<ID3DBlob> pContent;
};
