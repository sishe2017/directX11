#pragma once
#include <vector>
#include "../Type.h"
#include <wrl.h>
#include <d3d11.h>
#include <string>
#include <memory>

class VertexShader;

class InputAssembler
{
	friend class DirectX11;
	friend class DirectX11Pipeline;

	//顶点数据
	struct VertexData
	{
		//顶点数据缓存
		Microsoft::WRL::ComPtr<ID3D11Buffer> pVertex;
		//缓存中一个顶点的属性长度
		UINT stride = 0;
		//缓存开始读取的位置偏移
		UINT offset = 0;
	};
public:
	//设置绘制的基本图元
	void SetPrimitive(BasicPrimitive basicPrimitive);
	//关联顶点着色器
	void AssociateVertexShader(std::shared_ptr<VertexShader> pVertexShader);
	//设置顶点位置数据
	void SetVertexPos(std::vector<float> positions, UINT stride = 3 * sizeof(float), UINT offset = 0);
	//设置顶点索引数据
	void SetVertexIndex(std::vector<unsigned int> indices);
	//绑定输入装配阶段
	void Bind();

private:
	//基本图元默认是三角形
	D3D11_PRIMITIVE_TOPOLOGY basicPrimitive = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	//顶点位置数据
	VertexData vertexPosition;
	//顶点位置的布局
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	//顶点索引数据
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndex;
	//顶点属性集合
	std::vector<D3D11_INPUT_ELEMENT_DESC> vertexProperties;
	//关联的顶点着色器
	std::shared_ptr<VertexShader> pVertexShader;
	//顶点索引
	std::vector<unsigned int> indices;
};
