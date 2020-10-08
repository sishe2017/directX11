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

//单例模式
DirectX11& DirectX11::GetInstance()
{
	static DirectX11 directX11;
	return directX11;
}

//设置视口
void DirectX11::SetViewport()
{
	//视口
	D3D11_VIEWPORT viewport;
	//视口高度和宽度
	viewport.Width = 800;
	viewport.Height = 600;
	//深度的最小值和最大值
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	//绑定视口
	DirectX11::GetInstance().pContext->RSSetViewports(1, &viewport);
}

//初始化dx11
void DirectX11::Init(HWND hwnd, int width, int height)
{
	//对swap chain的描述信息
	DXGI_SWAP_CHAIN_DESC sd;
	//buffer分辨率的宽度和高度
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	//buffer的显示格式
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	//刷新频率
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	//不指定缩放比例
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	//不指定扫描线顺序
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//缓存数量为1
	sd.BufferCount = 1;
	//不适用多重采样
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	//缓存的用途是用来渲染输出的
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//输出的窗口句柄
	sd.OutputWindow = hwnd;
	//采用窗口模式
	sd.Windowed = TRUE;
	//sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	//采用bitblt模式
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	//创建设备和交换链
	D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG,
		nullptr, 0, D3D11_SDK_VERSION, &sd, &(GetInstance().pSwapChain), &(GetInstance().pDevice),
		nullptr, &(GetInstance().pContext));

	//获取渲染后缓冲帧缓存
	ComPtr<ID3D11Resource> pBackBuffer = nullptr;
	GetInstance().pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	//初始化渲染目标
	GetInstance().pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &(GetInstance().pTarget));

	//记录窗口宽度和高度
	GetInstance().width = width;
	GetInstance().height = height;

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	//开启深度测试
	depthStencilDesc.DepthEnable = TRUE;
	//允许写入深度缓存
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	//像素深度比较的时候，采用较低的深度值
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	ComPtr<ID3D11DepthStencilState> pDepthStencilState;
	GetInstance().pDevice->CreateDepthStencilState(&depthStencilDesc, &pDepthStencilState);

	//绑定深度缓存
	GetInstance().pContext->OMSetDepthStencilState(pDepthStencilState.Get(), 1);

	//创建深度模板缓存的纹理对象
	ComPtr<ID3D11Texture2D> pTexture;
	D3D11_TEXTURE2D_DESC textureDesc = {};
	//纹理的宽高
	textureDesc.Width = 800;
	textureDesc.Height = 600;
	//不适用mipmap
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	//格式使用32位
	textureDesc.Format = DXGI_FORMAT_D32_FLOAT;
	//不使用多重采样
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	//用途是默认用途：GPU可以读写这片缓存。
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	//绑定深度以及模板缓存
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	//创建2D纹理对象
	GetInstance().pDevice->CreateTexture2D(&textureDesc, nullptr, &pTexture);

	//创建深度模板缓存的视图描述对象
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
	depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	//创建深度模板视图
	GetInstance().pDevice->CreateDepthStencilView(pTexture.Get(), &depthStencilViewDesc, &(GetInstance().pDepthStencil));
	
	//绑定深度模板视图
	GetInstance().pContext->OMSetRenderTargets(
		1, GetInstance().pTarget.GetAddressOf(), GetInstance().pDepthStencil.Get());

	SetViewport();
}

//将内容输出到屏幕
void DirectX11::OutputToScreen()
{
	DirectX11* directX11 = &GetInstance();
	//显示帧缓存
	directX11->pSwapChain->Present(1, 0);
	//清空缓存
	DirectX11::SetBackground(0, 0, 0);
}

//设置背景
void DirectX11::SetBackground(float red, float green, float blue)
{
	float color[] = { red, green, blue, 1.0f };
	GetInstance().pContext->ClearRenderTargetView(GetInstance().pTarget.Get(), color);
	GetInstance().pContext->ClearDepthStencilView(GetInstance().pDepthStencil.Get(), D3D11_CLEAR_DEPTH, 1.0, 0);
}

//绘制内容至帧缓存
void DirectX11::Draw()
{
	//启动流水线
	DirectX11Pipeline::Start();
	//绘制图形
	GetInstance().pContext->DrawIndexed(
		static_cast<UINT>(DirectX11Pipeline::GetInstance().pInputAssembler->indices.size()),
		0, 0);
}

InputAssembler inputAssembler;
VertexShader vertexShader;
PixelShader pixelShader;
Matrix4x4 model;
Matrix4x4 perspective;
//绘制三角形，测试接口
void DirectX11::PrepareDrawTriangle(float angle, float z)
{
	//顶点索引缓存
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
	//顶点装配
	
	inputAssembler.SetPrimitive(BasicPrimitive::Triangle);
	inputAssembler.SetVertexPos(vertices);
	inputAssembler.SetVertexIndex(indieces);
	inputAssembler.AssociateVertexShader(L"CubeVS.cso");
	
	model = Matrix4x4::Translation(Vector3(0, 0, z)) * Matrix4x4::Rotation(Vector3(0, 0, 0));
	perspective = Matrix4x4::Perspective(1.0, 3.0f / 4.0f, 0.5f, 10.0f);
	
	vertexShader.Load(L"CubeVS.cso");

	//像素着色器
	//立方体的面颜色
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

	//绘制图形
	GetInstance().pContext->DrawIndexed(36, 0, 0);
}
