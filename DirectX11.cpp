#include "DirectX11.h"
#include "Vector2.h"
#include "Vector3.h"
#include <vector>
#include <DirectXMath.h>
#include "Matrix4x4.h"

#include "InputAssembler.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "DirectX11Pipeline.h"
#include "Time.h"

using namespace Microsoft::WRL;

//����ģʽ
DirectX11& DirectX11::GetInstance()
{
	static DirectX11 directX11;
	return directX11;
}

//�����ӿ�
void DirectX11::SetViewport()
{
	//�ӿ�
	D3D11_VIEWPORT viewport;
	//�ӿڸ߶ȺͿ��
	viewport.Width = 800;
	viewport.Height = 600;
	//��ȵ���Сֵ�����ֵ
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	//���ӿ�
	DirectX11::GetInstance().pContext->RSSetViewports(1, &viewport);
}

//��ʼ��dx11
void DirectX11::Init(HWND hwnd, int width, int height)
{
	//��swap chain��������Ϣ
	DXGI_SWAP_CHAIN_DESC sd;
	//buffer�ֱ��ʵĿ�Ⱥ͸߶�
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	//buffer����ʾ��ʽ
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	//ˢ��Ƶ��
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	//��ָ�����ű���
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	//��ָ��ɨ����˳��
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//��������Ϊ1
	sd.BufferCount = 1;
	//�����ö��ز���
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	//�������;��������Ⱦ�����
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//����Ĵ��ھ��
	sd.OutputWindow = hwnd;
	//���ô���ģʽ
	sd.Windowed = TRUE;
	//sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	//����bitbltģʽ
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	//�����豸�ͽ�����
	D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG,
		nullptr, 0, D3D11_SDK_VERSION, &sd, &(GetInstance().pSwapChain), &(GetInstance().pDevice),
		nullptr, &(GetInstance().pContext));

	//��ȡ��Ⱦ�󻺳�֡����
	ComPtr<ID3D11Resource> pBackBuffer = nullptr;
	GetInstance().pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	//��ʼ����ȾĿ��
	GetInstance().pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &(GetInstance().pTarget));

	//��¼���ڿ�Ⱥ͸߶�
	GetInstance().width = width;
	GetInstance().height = height;

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	//������Ȳ���
	depthStencilDesc.DepthEnable = TRUE;
	//����д����Ȼ���
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	//������ȱȽϵ�ʱ�򣬲��ýϵ͵����ֵ
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	ComPtr<ID3D11DepthStencilState> pDepthStencilState;
	GetInstance().pDevice->CreateDepthStencilState(&depthStencilDesc, &pDepthStencilState);

	//����Ȼ���
	GetInstance().pContext->OMSetDepthStencilState(pDepthStencilState.Get(), 1);

	//�������ģ�建����������
	ComPtr<ID3D11Texture2D> pTexture;
	D3D11_TEXTURE2D_DESC textureDesc = {};
	//����Ŀ��
	textureDesc.Width = 800;
	textureDesc.Height = 600;
	//������mipmap
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	//��ʽʹ��32λ
	textureDesc.Format = DXGI_FORMAT_D32_FLOAT;
	//��ʹ�ö��ز���
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	//��;��Ĭ����;��GPU���Զ�д��Ƭ���档
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	//������Լ�ģ�建��
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	//����2D�������
	GetInstance().pDevice->CreateTexture2D(&textureDesc, nullptr, &pTexture);

	//�������ģ�建�����ͼ��������
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
	depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	//�������ģ����ͼ
	GetInstance().pDevice->CreateDepthStencilView(pTexture.Get(), &depthStencilViewDesc, &(GetInstance().pDepthStencil));
	
	//�����ģ����ͼ
	GetInstance().pContext->OMSetRenderTargets(
		1, GetInstance().pTarget.GetAddressOf(), GetInstance().pDepthStencil.Get());

	SetViewport();
}

//�������������Ļ
void DirectX11::OutputToScreen()
{
	DirectX11* directX11 = &GetInstance();
	//��ʾ֡����
	directX11->pSwapChain->Present(1, 0);
	//��ջ���
	DirectX11::SetBackground(0, 0, 0);
}

//���ñ���
void DirectX11::SetBackground(float red, float green, float blue)
{
	float color[] = { red, green, blue, 1.0f };
	GetInstance().pContext->ClearRenderTargetView(GetInstance().pTarget.Get(), color);
	GetInstance().pContext->ClearDepthStencilView(GetInstance().pDepthStencil.Get(), D3D11_CLEAR_DEPTH, 1.0, 0);
}

//����������֡����
void DirectX11::Draw()
{
	//������ˮ��
	DirectX11Pipeline::Start();
	//����ͼ��
	GetInstance().pContext->DrawIndexed(
		static_cast<UINT>(DirectX11Pipeline::GetInstance().pInputAssembler->indices.size()),
		0, 0);
}

InputAssembler inputAssembler;
VertexShader vertexShader;
PixelShader pixelShader;
Matrix4x4 model;
Matrix4x4 perspective;
//���������Σ����Խӿ�
void DirectX11::PrepareDrawTriangle(float angle, float z)
{
	//������������
	std::vector<unsigned int> indieces{
		1, 0, 2, 1, 2, 3,
		4, 0, 1, 4, 1, 5,
		1, 3, 5, 3, 7, 5,
		0, 4, 6, 0, 6, 2,
		4, 5, 6, 5, 7, 6,
		3, 6, 7, 2, 6, 3
	};
	std::vector<float> vertices
	{
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
	};
	//����װ��
	
	inputAssembler.SetPrimitive(BasicPrimitive::Triangle);
	inputAssembler.SetVertexPos(vertices);
	inputAssembler.SetVertexIndex(indieces);
	inputAssembler.AssociateVertexShader(L"CubeVS.cso");
	
	model = Matrix4x4::Translation(Vector3(0, 0, z)) * Matrix4x4::Rotation(Vector3(0, 0, 0));
	perspective = Matrix4x4::Perspective(1.0, 3.0f / 4.0f, 0.5f, 10.0f);
	
	vertexShader.Load(L"CubeVS.cso");

	//������ɫ��
	//�����������ɫ
	std::vector<float> colors =
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 0.0f,
	};
	
	pixelShader.Load(L"CubePS.cso");
	pixelShader.SetConstant(colors, 0);
}

void DirectX11::DrawTriangle()
{
	inputAssembler.Bind();
	model = Matrix4x4::Rotation(Vector3(Time::deltaTime, Time::deltaTime, Time::deltaTime)) * model;
	vertexShader.SetConstant(Matrix4x4::Transpose(model * perspective), 0);
	vertexShader.Bind();
	pixelShader.Bind();

	//����ͼ��
	GetInstance().pContext->DrawIndexed(36, 0, 0);
}
