#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

class DirectX11
{
	friend class ConstantBuffer;
	friend class InputAssembler;
	friend class VertexShader;
	friend class PixelShader;
	friend class Texture;
	friend class Sampler;

public:

	//初始化dx11
	static void Init(HWND hwnd, int width, int height);
	//将内容输出到屏幕
	static void OutputToScreen();
	//设置背景
	static void SetBackground(float red, float green, float blue);
	//绘制内容至帧缓存
	static void Draw();

private:
	//单例模式
	DirectX11() = default;
	DirectX11(const DirectX11&) = delete;
	DirectX11& operator=(const DirectX11&) = delete;
	static DirectX11& GetInstance();

	//创建的资源的接口
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	//存储渲染数据的接口
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	//与渲染命令相关的接口
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	//渲染目标视图
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	//深度模板缓存视图
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepthStencil;
	//窗口宽度和高度
	int width = 0;
	int height = 0;

	//设置视口
	static void SetViewport();
};

