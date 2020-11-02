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

public:
	//设置绘制的基本图元
	void SetPrimitive(BasicPrimitive basicPrimitive);
	//关联顶点着色器
	void AssociateVertexShader(std::shared_ptr<VertexShader> pVertexShader);
	//设置顶点所有数据
	void SetVertexData(std::vector<float> data, std::vector<unsigned int> strides, std::vector<std::string> semantics);
	//设置顶点位置数据
	void SetVertexPos(std::vector<float> positions, UINT stride = 3 * sizeof(float));
	//设置顶点纹理坐标
	void SetVertexTexCoord(std::vector<float> texCoords);
	//设置顶点索引数据
	void SetVertexIndex(std::vector<unsigned int> &indices);
	//把顶点的数据绑定输入装配阶段
	void BindVertexData();

private:
	//基本图元默认是三角形
	D3D11_PRIMITIVE_TOPOLOGY basicPrimitive = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	//顶点位置的布局
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	//顶点索引数据
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndex;
	//顶点属性描述集合
	std::vector<D3D11_INPUT_ELEMENT_DESC> vertexDescs;
	//顶点数据集合
	std::vector<std::vector<float>> vertexDatas;
	//关联的顶点着色器
	std::shared_ptr<VertexShader> pVertexShader;
	//顶点索引
	std::vector<unsigned int> indices;
	//数据步长集合
	std::vector<unsigned int> strides;
	//dx11 buffer
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;

	//获取数据现有的步长
	unsigned int GetCurrentStride();
};
