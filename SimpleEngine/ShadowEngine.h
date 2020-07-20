#pragma once
#include <string>
#include <wrl/client.h>
#include <d3d11_1.h>

#include "Window.h"

#pragma comment(lib, "d3d11.lib")

//阴影引擎（自创的哈哈）
class ShadowEngine
{
	friend LRESULT CALLBACK MainWindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	ShadowEngine(HINSTANCE hInstance, std::wstring title, int width, int height);
	//开启或者关闭多重采样
	void MSAA(bool flag);
	//引擎初始化
	void Init();
	//引擎运行
	void Run();
	virtual ~ShadowEngine();

private:

	HINSTANCE hGame;									//游戏实例句柄
	HWND hMainWindow;									//窗口句柄
	bool sampleFlag;									//多重采样标志
	UINT msaaQuality;									//多重采样质量等级

	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
	//Direct3D 11.0
	ComPtr<ID3D11Device> d3dDevice11_0;					//d3d11.0设备
	ComPtr<ID3D11DeviceContext> d3dDeviceContext11_0;	//d3d11.0设备上下文
	ComPtr<IDXGISwapChain> dxgiSwapChain11_0;			//dxgi11.0交换链
	//Direct3D 11.1
	ComPtr<ID3D11Device1> d3dDevice11_1;				//d3d11.1设备
	ComPtr<ID3D11DeviceContext1> d3dDeviceContext11_1;	//d3d11.1设备上下文
	ComPtr<IDXGISwapChain1> dxgiSwapChain11_1;			//dxgi11.1交换链
	//常用资源
	ComPtr<ID3D11Texture2D> depthStencilBuffer;			// 深度模板缓冲区
	ComPtr<ID3D11RenderTargetView> renderTargetView;	// 渲染目标视图
	ComPtr<ID3D11DepthStencilView> m_pDepthStencilView; // 深度模板视图
	D3D11_VIEWPORT m_ScreenViewport;                    // 视口

	int viewPortWidth;									//视口宽度
	int viewPortHeight;									//视口高度

	//主窗口
	Window mainWindow;

	//初始化DirectX11.1
	void InitDirectX11_1();
	//窗口尺寸变化的时候，调用的函数
	void Update();
	//绘制场景
	void DrawScene();
	//窗口消息处理
	virtual LRESULT MessageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

