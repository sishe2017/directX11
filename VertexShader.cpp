#include "VertexShader.h"
#include <d3dcompiler.h>
#include "DirectX11.h"

//���ض�����ɫ��
void VertexShader::Load(std::wstring path)
{
	D3DReadFileToBlob(path.c_str(), &pContent);
	DirectX11::GetInstance().pDevice->CreateVertexShader(
		pContent->GetBufferPointer(), pContent->GetBufferSize(),
		nullptr, &pVertexShader
	);
}

//�󶨶�����ɫ��
void VertexShader::Bind()
{
	//�󶨶�����ɫ��
	DirectX11::GetInstance().pContext->VSSetShader(pVertexShader.Get(), nullptr, 0);
	//�󶨳���
	for (int i = 0; i < datas.size(); i++)
		DirectX11::GetInstance().pContext->VSSetConstantBuffers(0, 1, datas[i].pBuffer.GetAddressOf());
}

//���ö�����ɫ���еĳ���
void VertexShader::SetConstant(ConstantBuffer constantBuffer, unsigned int index)
{
	//���밴��shader�ı���˳����и�ֵ
	if (index > datas.size())
		throw "set constant variable out of order";
	//��¼�µĳ���
	else if (index == datas.size())
		datas.push_back(constantBuffer);
	//�ı䳣��
	else
		datas[index] = constantBuffer;
}