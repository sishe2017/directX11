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
	if (vs != GetInstance().pVertexShader)
	{
		GetInstance().pVertexShader = vs;
		GetInstance().hasModifyVS = true;
	}
}

//��PS
void DirectX11Pipeline::BindPixelShader(std::shared_ptr<PixelShader> ps)
{
	if (ps != GetInstance().pPixelShader)
	{
		GetInstance().pPixelShader = ps;
		GetInstance().hasModifyPS = true;
	}
}

//������ˮ��
void DirectX11Pipeline::Start()
{
	//����װ�����ǿգ��󶨶�����ɫ��
	if (GetInstance().pInputAssembler)
		GetInstance().pInputAssembler->BindVertexData();
	//������
	else
	{
		throw "not set input assembler";
	}

	//������ɫ���޸Ĺ������°󶨶�����ɫ��
	if (GetInstance().hasModifyVS)
	{
		GetInstance().pVertexShader->Bind();
		GetInstance().hasModifyVS = false;
	}
	else if (GetInstance().pVertexShader == nullptr)
	{
		throw "not set vertex shader";
	}

	//������ɫ���ǿհ�������ɫ��
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
