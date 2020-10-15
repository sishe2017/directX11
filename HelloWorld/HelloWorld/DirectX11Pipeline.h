#pragma once
#include <vector>
#include <memory>
#include "DirectX11/InputAssembler.h"
#include "DirectX11/VertexShader.h"
#include "DirectX11/PixelShader.h"

class DirectX11Pipeline
{
	friend class DirectX11;
public:
	//绑定IA
	static void BindInputAssembler(std::shared_ptr<InputAssembler> ia);
	//绑定VS
	static void BindVertexShader(std::shared_ptr<VertexShader> vs);
	//绑定PS
	static void BindPixelShader(std::shared_ptr<PixelShader> ps);
	//启用流水线
	static void Start();

private:
	//单例模式
	DirectX11Pipeline() = default;
	DirectX11Pipeline(const DirectX11Pipeline&) = delete;
	DirectX11Pipeline& operator=(const DirectX11Pipeline&) = delete;
	static DirectX11Pipeline& GetInstance();
	//顶点装配阶段
	std::shared_ptr<InputAssembler> pInputAssembler;
	//顶点着色器
	std::shared_ptr<VertexShader> pVertexShader;
	//像素着色器
	std::shared_ptr<PixelShader> pPixelShader;
};
