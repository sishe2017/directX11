#include "DirectX11Pipeline.h"

using namespace std;


//��IA
void DirectX11Pipeline::BindInputAssembler(std::shared_ptr<InputAssembler> ia)
{
	GetInstance().pInputAssembler = ia;
}

//��VS
void DirectX11Pipeline::BindVertexShader(std::shared_ptr<VertexShader> vs)
{
	GetInstance().pVertexShader = vs;
}

//��PS
void DirectX11Pipeline::BindPixelShader(std::shared_ptr<PixelShader> ps)
{
	GetInstance().pPixelShader = ps;
}

//������ˮ��
void DirectX11Pipeline::Start()
{
	auto directX11Pipeline = &(DirectX11Pipeline::GetInstance());
	//����װ�����ǿգ��󶨶�����ɫ��
	if (directX11Pipeline->pInputAssembler)
		directX11Pipeline->pInputAssembler->Bind();
	//������
	else
		throw "not set input assembler";
	//������ɫ���ǿհ󶨶�����ɫ��
	if (directX11Pipeline->pVertexShader)
		directX11Pipeline->pVertexShader->Bind();
	else
		throw "not set vertex shader";
	//������ɫ���ǿհ�������ɫ��
	if (directX11Pipeline->pPixelShader)
		directX11Pipeline->pPixelShader->Bind();
}

DirectX11Pipeline& DirectX11Pipeline::GetInstance()
{
	static DirectX11Pipeline instance;
	return instance;
}
