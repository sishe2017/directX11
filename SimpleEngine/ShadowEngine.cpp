#include "ShadowEngine.h"

//�ص�ָ��
ShadowEngine *cbPtr = nullptr;

//�����ڴ���ص�
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
	//����ȫ�ֻص�ָ��
	//cbPtr = this;

	//��ʼ������
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
	//��ʼ��11.1
	InitDirectX11_1();
}

void ShadowEngine::Run()
{
	MSG msg;
	//��Ӧ�ó������Ϣ�����л�ȡ��Ϣ
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//����Ϣ������ַ�
		TranslateMessage(&msg);
		//����Ϣ���͵����ڣ�����WndProc�ص�
		DispatchMessage(&msg);
	}
}

ShadowEngine::~ShadowEngine()
{
}

void ShadowEngine::InitDirectX11_1()
{
	//����ģʽ�£����d3d�豸������Ϣ
	UINT flags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // DEBUG
	//���Եȼ�11.1
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_1;
	D3D_FEATURE_LEVEL outputFeatureLevel;
	//����d3d11�豸��Ӳ�����������Եȼ�11.1
	auto ret = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags, &featureLevel, 
		1, D3D11_SDK_VERSION, d3dDevice11_0.GetAddressOf(), &outputFeatureLevel,
		d3dDeviceContext11_0.GetAddressOf());
	if (!SUCCEEDED(ret))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return;
	}

	ComPtr<IDXGIDevice> dxgiDevice = nullptr;					//dxgi�豸
	ComPtr<IDXGIAdapter> dxgiAdapter = nullptr;					//dxgi������
	ComPtr<IDXGIFactory1> dxgiFactory1_1 = nullptr;				// DXGI1.1�Ľӿ���
	ComPtr<IDXGIFactory2> dxgiFactory1_2 = nullptr;				// DXGI1.2�Ľӿ���

	//ͨ��dx11.0�豸��ȡ��dxgi�豸
	d3dDevice11_0.As(&dxgiDevice);
	//��ͨ��dxgi�豸��ȡdxgi������
	dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf());
	//ͨ��dxgi��������ȡdxgi1.1�Ľӿ�
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(dxgiFactory1_1.GetAddressOf()));

	//��ȡDXGI1.2�Ľӿ�
	dxgiFactory1_1.As(&dxgiFactory1_2);
	//��ȡd3d11.1���豸�������Ļ���
	d3dDevice11_0.As(&d3dDevice11_1);
	d3dDevice11_0.As(&d3dDeviceContext11_1);

	//���DXGI_SWAP_CHAIN_DESC1
	DXGI_SWAP_CHAIN_DESC1 swapChain;
	swapChain.Width = viewPortWidth;
	swapChain.Height = viewPortHeight;
	swapChain.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//���ݱ�־�Ƿ���ж��ز���
	if (sampleFlag)
	{
		swapChain.SampleDesc.Count = 4;
		//���MSAA֧�ֵ������ȼ�
		d3dDevice11_0->CheckMultisampleQualityLevels(
			DXGI_FORMAT_R8G8B8A8_UNORM, 4, &msaaQuality);
		//��������С����ߵȼ�
		swapChain.SampleDesc.Quality = msaaQuality - 1;
	}
	else
	{
		swapChain.SampleDesc.Count = 1;
		swapChain.SampleDesc.Quality = 0;
	}
	swapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChain.BufferCount = 1;
	//ָ��λ�����ķ�ʽ
	swapChain.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChain.Flags = 0;

	//���DXGI_SWAP_CHAIN_FULLSCREEN_DESC�ṹ��
	DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainFullScreenInfo;
	swapChainFullScreenInfo.RefreshRate.Numerator = 60;
	swapChainFullScreenInfo.RefreshRate.Denominator = 1;
	swapChainFullScreenInfo.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainFullScreenInfo.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainFullScreenInfo.Windowed = true;

	//��ֹAlt+Enterȫ������
	dxgiFactory1_1->MakeWindowAssociation(hMainWindow, DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_WINDOW_CHANGES);

	//����dxgi������
	dxgiFactory1_2->CreateSwapChainForHwnd(d3dDevice11_0.Get(), hMainWindow, &swapChain,
		&swapChainFullScreenInfo, nullptr, dxgiSwapChain11_1.GetAddressOf());
}

void ShadowEngine::Update()
{
}

void ShadowEngine::DrawScene()
{
	//����ɫ�����ɫ����
	static float blue[4] = { 0,0,1.0f,0 };
}

LRESULT ShadowEngine::MessageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//�����յ��Ĳ�ͬ��Ϣ���д���
	switch (msg)
	{
		//�յ����ٴ��ڵ���Ϣ�����˳�����
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
