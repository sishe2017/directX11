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
	GetInstance().pVertexShader = vs;
}

//绑定PS
void DirectX11Pipeline::BindPixelShader(std::shared_ptr<PixelShader> ps)
{
	GetInstance().pPixelShader = ps;
}

//启用流水线
void DirectX11Pipeline::Start()
{
	auto directX11Pipeline = &(DirectX11Pipeline::GetInstance());
	//顶点装配器非空，绑定顶点着色器
	if (directX11Pipeline->pInputAssembler)
		directX11Pipeline->pInputAssembler->Bind();
	//错误处理
	else
		throw "not set input assembler";
	//顶点着色器非空绑定顶点着色器
	if (directX11Pipeline->pVertexShader)
		directX11Pipeline->pVertexShader->Bind();
	else
		throw "not set vertex shader";
	//像素着色器非空绑定像素着色器
	if (directX11Pipeline->pPixelShader)
		directX11Pipeline->pPixelShader->Bind();
}

DirectX11Pipeline& DirectX11Pipeline::GetInstance()
{
	static DirectX11Pipeline instance;
	return instance;
}
