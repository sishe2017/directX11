#include "ShadowEngine.h"

//回调指针
ShadowEngine *cbPtr = nullptr;

//主窗口处理回调
LRESULT CALLBACK MainWindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return cbPtr->MessageProc(hwnd, msg, wParam, lParam);
}

ShadowEngine::ShadowEngine(HINSTANCE hInstance, std::wstring title, int width, int height):
	hGame(hInstance),
	viewPortWidth(width),
	viewPortHeight(height),
	sampleFlag(false),
	mainWindow(Window(hInstance,title))
{
	//设置全局回调指针
	//cbPtr = this;

	//初始化窗口
	mainWindow.SetSize(width, height);
	mainWindow.ShowWindow();
}

void ShadowEngine::MSAA(bool flag)
{
	if (flag)
		sampleFlag = true;
	else
		sampleFlag = false;
}

void ShadowEngine::Init()
{
	//初始化11.1
	InitDirectX11_1();
}

void ShadowEngine::Run()
{
	MSG msg;
	//从应用程序的消息队列中获取消息
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//将消息翻译成字符
		TranslateMessage(&msg);
		//将消息发送到窗口，出发WndProc回调
		DispatchMessage(&msg);
	}
}

ShadowEngine::~ShadowEngine()
{
}

void ShadowEngine::InitDirectX11_1()
{
	//调试模式下，输出d3d设备调试信息
	UINT flags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // DEBUG
	//特性等级11.1
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_1;
	D3D_FEATURE_LEVEL outputFeatureLevel;
	//创建d3d11设备：硬件驱动，特性等级11.1
	auto ret = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags, &featureLevel, 
		1, D3D11_SDK_VERSION, d3dDevice11_0.GetAddressOf(), &outputFeatureLevel,
		d3dDeviceContext11_0.GetAddressOf());
	if (!SUCCEEDED(ret))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return;
	}

	ComPtr<IDXGIDevice> dxgiDevice = nullptr;					//dxgi设备
	ComPtr<IDXGIAdapter> dxgiAdapter = nullptr;					//dxgi适配器
	ComPtr<IDXGIFactory1> dxgiFactory1_1 = nullptr;				// DXGI1.1的接口类
	ComPtr<IDXGIFactory2> dxgiFactory1_2 = nullptr;				// DXGI1.2的接口类

	//通过dx11.0设备获取到dxgi设备
	d3dDevice11_0.As(&dxgiDevice);
	//在通过dxgi设备获取dxgi适配器
	dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf());
	//通过dxgi适配器获取dxgi1.1的接口
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(dxgiFactory1_1.GetAddressOf()));

	//获取DXGI1.2的接口
	dxgiFactory1_1.As(&dxgiFactory1_2);
	//获取d3d11.1的设备和上下文环境
	d3dDevice11_0.As(&d3dDevice11_1);
	d3dDevice11_0.As(&d3dDeviceContext11_1);

	//填充DXGI_SWAP_CHAIN_DESC1
	DXGI_SWAP_CHAIN_DESC1 swapChain;
	swapChain.Width = viewPortWidth;
	swapChain.Height = viewPortHeight;
	swapChain.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//根据标志是否进行多重采样
	if (sampleFlag)
	{
		swapChain.SampleDesc.Count = 4;
		//检测MSAA支持的质量等级
		d3dDevice11_0->CheckMultisampleQualityLevels(
			DXGI_FORMAT_R8G8B8A8_UNORM, 4, &msaaQuality);
		//质量必须小于最高等级
		swapChain.SampleDesc.Quality = msaaQuality - 1;
	}
	else
	{
		swapChain.SampleDesc.Count = 1;
		swapChain.SampleDesc.Quality = 0;
	}
	swapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChain.BufferCount = 1;
	//指定位拷贝的方式
	swapChain.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChain.Flags = 0;

	//填充DXGI_SWAP_CHAIN_FULLSCREEN_DESC结构体
	DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainFullScreenInfo;
	swapChainFullScreenInfo.RefreshRate.Numerator = 60;
	swapChainFullScreenInfo.RefreshRate.Denominator = 1;
	swapChainFullScreenInfo.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainFullScreenInfo.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainFullScreenInfo.Windowed = true;

	//禁止Alt+Enter全屏操作
	dxgiFactory1_1->MakeWindowAssociation(hMainWindow, DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_WINDOW_CHANGES);

	//创建dxgi交换链
	dxgiFactory1_2->CreateSwapChainForHwnd(d3dDevice11_0.Get(), hMainWindow, &swapChain,
		&swapChainFullScreenInfo, nullptr, dxgiSwapChain11_1.GetAddressOf());
}

void ShadowEngine::Update()
{
}

void ShadowEngine::DrawScene()
{
	//用蓝色清楚颜色缓存
	static float blue[4] = { 0,0,1.0f,0 };
}

LRESULT ShadowEngine::MessageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//根据收到的不同消息进行处理
	switch (msg)
	{
		//收到销毁窗口的消息，则退出程序
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
