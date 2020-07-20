#pragma once
#include <string>
#include <wrl/client.h>
#include <d3d11_1.h>

#include "Window.h"

#pragma comment(lib, "d3d11.lib")

//��Ӱ���棨�Դ��Ĺ�����
class ShadowEngine
{
	friend LRESULT CALLBACK MainWindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	ShadowEngine(HINSTANCE hInstance, std::wstring title, int width, int height);
	//�������߹رն��ز���
	void MSAA(bool flag);
	//�����ʼ��
	void Init();
	//��������
	void Run();
	virtual ~ShadowEngine();

private:

	HINSTANCE hGame;									//��Ϸʵ�����
	HWND hMainWindow;									//���ھ��
	bool sampleFlag;									//���ز�����־
	UINT msaaQuality;									//���ز��������ȼ�

	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
	//Direct3D 11.0
	ComPtr<ID3D11Device> d3dDevice11_0;					//d3d11.0�豸
	ComPtr<ID3D11DeviceContext> d3dDeviceContext11_0;	//d3d11.0�豸������
	ComPtr<IDXGISwapChain> dxgiSwapChain11_0;			//dxgi11.0������
	//Direct3D 11.1
	ComPtr<ID3D11Device1> d3dDevice11_1;				//d3d11.1�豸
	ComPtr<ID3D11DeviceContext1> d3dDeviceContext11_1;	//d3d11.1�豸������
	ComPtr<IDXGISwapChain1> dxgiSwapChain11_1;			//dxgi11.1������
	//������Դ
	ComPtr<ID3D11Texture2D> depthStencilBuffer;			// ���ģ�建����
	ComPtr<ID3D11RenderTargetView> renderTargetView;	// ��ȾĿ����ͼ
	ComPtr<ID3D11DepthStencilView> m_pDepthStencilView; // ���ģ����ͼ
	D3D11_VIEWPORT m_ScreenViewport;                    // �ӿ�

	int viewPortWidth;									//�ӿڿ��
	int viewPortHeight;									//�ӿڸ߶�

	//������
	Window mainWindow;

	//��ʼ��DirectX11.1
	void InitDirectX11_1();
	//���ڳߴ�仯��ʱ�򣬵��õĺ���
	void Update();
	//���Ƴ���
	void DrawScene();
	//������Ϣ����
	virtual LRESULT MessageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

