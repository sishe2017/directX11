#include "PixelShader.h"
#include <d3dcompiler.h>
#include "../DirectX11.h"

//����������ɫ��
void PixelShader::Load(std::wstring path)
{
	D3DReadFileToBlob(path.c_str(), &pContent);
	DirectX11::GetInstance().pDevice->CreatePixelShader(
		pContent->GetBufferPointer(), pContent->GetBufferSize(),
		nullptr, &pPixelShader
	);
}

//��������ɫ��
void PixelShader::Bind()
{
	//�󶨶�����ɫ��
	DirectX11::GetInstance().pContext->PSSetShader(pPixelShader.Get(), nullptr, 0);
	//�󶨳���
	for (int i = 0; i < datas.size(); i++)
		DirectX11::GetInstance().pContext->PSSetConstantBuffers(0, 1, datas[i].pBuffer.GetAddressOf());
}

//����������ɫ���еĳ���
void PixelShader::SetConstant(ConstantBuffer constantBuffer, unsigned int index)
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