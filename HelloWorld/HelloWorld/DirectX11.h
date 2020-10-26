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

	//��ʼ��dx11
	static void Init(HWND hwnd, int width, int height);
	//�������������Ļ
	static void OutputToScreen();
	//���ñ���
	static void SetBackground(float red, float green, float blue);
	//����������֡����
	static void Draw();

private:
	//����ģʽ
	DirectX11() = default;
	DirectX11(const DirectX11&) = delete;
	DirectX11& operator=(const DirectX11&) = delete;
	static DirectX11& GetInstance();

	//��������Դ�Ľӿ�
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	//�洢��Ⱦ���ݵĽӿ�
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	//����Ⱦ������صĽӿ�
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	//��ȾĿ����ͼ
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	//���ģ�建����ͼ
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepthStencil;
	//���ڿ�Ⱥ͸߶�
	int width = 0;
	int height = 0;

	//�����ӿ�
	static void SetViewport();
};

