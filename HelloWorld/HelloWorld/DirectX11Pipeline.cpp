#include "DirectX11Pipeline.h"

using namespace std;

//绑定IA
void DirectX11Pipeline::BindInputAssembler(std::shared_ptr<InputAssembler> ia)
{
	GetInstance().pInputAssembler = ia;
}

//绑定VS
void DirectX11Pipeline::BindVertexShader(std::shared_ptr<VertexShader> vs)
{
	if (vs != GetInstance().pVertexShader)
	{
		GetInstance().pVertexShader = vs;
		GetInstance().hasModifyVS = true;
	}
}

//绑定PS
void DirectX11Pipeline::BindPixelShader(std::shared_ptr<PixelShader> ps)
{
	if (ps != GetInstance().pPixelShader)
	{
		GetInstance().pPixelShader = ps;
		GetInstance().hasModifyPS = true;
	}
}

//启用流水线
void DirectX11Pipeline::Start()
{
	//顶点装配器非空，绑定顶点着色器
	if (GetInstance().pInputAssembler)
		GetInstance().pInputAssembler->BindVertexData();
	//错误处理
	else
	{
		throw "not set input assembler";
	}

	//顶点着色器修改过则重新绑定顶点着色器
	if (GetInstance().hasModifyVS)
	{
		GetInstance().pVertexShader->Bind();
		GetInstance().hasModifyVS = false;
	}
	else if (GetInstance().pVertexShader == nullptr)
	{
		throw "not set vertex shader";
	}

	//像素着色器非空绑定像素着色器
	if (GetInstance().hasModifyPS)
	{
		GetInstance().pPixelShader->Bind();
		GetInstance().hasModifyPS = false;
	}
	else if (GetInstance().pPixelShader == nullptr)
	{
		throw "not set pixel shader";
	}
}

DirectX11Pipeline& DirectX11Pipeline::GetInstance()
{
	static DirectX11Pipeline instance;
	return instance;
}
