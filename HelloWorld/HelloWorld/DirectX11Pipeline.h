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
	//��IA
	static void BindInputAssembler(std::shared_ptr<InputAssembler> ia);
	//��VS
	static void BindVertexShader(std::shared_ptr<VertexShader> vs);
	//��PS
	static void BindPixelShader(std::shared_ptr<PixelShader> ps);
	//������ˮ��
	static void Start();

private:
	//����ģʽ
	DirectX11Pipeline() = default;
	DirectX11Pipeline(const DirectX11Pipeline&) = delete;
	DirectX11Pipeline& operator=(const DirectX11Pipeline&) = delete;
	static DirectX11Pipeline& GetInstance();
	//����װ��׶�
	std::shared_ptr<InputAssembler> pInputAssembler;
	//������ɫ��
	std::shared_ptr<VertexShader> pVertexShader;
	//������ɫ��
	std::shared_ptr<PixelShader> pPixelShader;
};
