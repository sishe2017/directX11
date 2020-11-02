#include "InputAssembler.h"
#include "../DirectX11.h"
#include "VertexShader.h"

using namespace Microsoft::WRL;
using namespace std;

//把一个顶点的所有数据绑定输入装配阶段
void InputAssembler::BindVertexData()
{
	//顶点着色器未关联直接抛出异常
	if (!pVertexShader)
		throw "vertex not associate";

	//将顶点的数据集合成一维数组
	vector<float> vertexData;
	for (int i = 0; i < vertexDatas.size(); i++)
		for (int j = 0; j < vertexDatas[i].size(); j++)
			vertexData.push_back(vertexDatas[i][j]);

	//缓存描述信息
	D3D11_BUFFER_DESC bufferDesc;
	//标志缓存用于顶点缓存
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//用途是默认用途：GPU可以读写这片缓存
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//CPU不可访问这片内存
	bufferDesc.CPUAccessFlags = 0;
	//不适用其他杂项标志
	bufferDesc.MiscFlags = 0;
	//缓存的大小，以字节为单位
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(float) * this->stride);
	//每个顶点的大小
	// todo:目前没看到这个属性的作用
	bufferDesc.StructureByteStride = 0;
	//设置常量缓存存储的数据
	D3D11_SUBRESOURCE_DATA sourceData;
	sourceData.pSysMem = vertexData.data();
	//创建顶点位置缓存对象
	DirectX11::GetInstance().pDevice->CreateBuffer(&bufferDesc, &sourceData, &(buffer));

	//创建顶点布局
	DirectX11::GetInstance().pDevice->CreateInputLayout(
		vertexDescs.data(), UINT(vertexDescs.size()), pVertexShader->pContent->GetBufferPointer(),
		pVertexShader->pContent->GetBufferSize(), &pInputLayout);
	//绑定顶点位置布局
	DirectX11::GetInstance().pContext->IASetInputLayout(this->pInputLayout.Get());
	//绑定顶点缓存
	UINT offset = 0;
	DirectX11::GetInstance().pContext->IASetVertexBuffers(
		0, 1, buffer.GetAddressOf(), &stride, &offset);
	//绑定顶点索引缓存
	DirectX11::GetInstance().pContext->IASetIndexBuffer(pIndex.Get(), DXGI_FORMAT_R32_UINT, 0);
	//设置图元装配的目标图元
	DirectX11::GetInstance().pContext->IASetPrimitiveTopology(this->basicPrimitive);
}

//设置顶点位置数据
void InputAssembler::SetVertexPos(std::vector<float> pos, UINT stride)
{
	//顶点位置信息描述
	D3D11_INPUT_ELEMENT_DESC posDesc;
	//顶点着色器中的位置的语义名字
	posDesc.SemanticName = "POSITION";
	//语义索引，当程序中含有相同的语义的时候，我们需要使用语义索引进行区分
	posDesc.SemanticIndex = 0;
	//传入的数据的类型
	posDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	//输入槽编号
	posDesc.InputSlot = 0;
	//读取数据的起始位置偏移
	posDesc.AlignedByteOffset = 0;
	//输入槽中数据的类型
	posDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	//实例绘制的个数
	posDesc.InstanceDataStepRate = 0;

	//记录顶点属性描述
	vertexDescs.push_back(posDesc);
	//记录顶点数据
	vertexDatas.push_back(pos);
	//记录步长
	this->stride += stride;
}

//设置顶点纹理坐标
void InputAssembler::SetVertexTexCoord(std::vector<float> texCoords)
{
	//顶点纹理坐标信息描述
	D3D11_INPUT_ELEMENT_DESC textureDesc;
	//顶点着色器中的纹理坐标的语义名字
	textureDesc.SemanticName = "TEXCOORD";
	//语义索引，当程序中含有相同的语义的时候，我们需要使用语义索引进行区分
	textureDesc.SemanticIndex = 0;
	//传入的数据的类型
	textureDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
	//输入槽编号，
	textureDesc.InputSlot = 0;
	//读取数据的起始位置偏移
	textureDesc.AlignedByteOffset = 0;
	//输入槽中数据的类型
	textureDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	//实例绘制的个数
	textureDesc.InstanceDataStepRate = 0;

	//记录顶点属性描述
	vertexDescs.push_back(textureDesc);
	//记录顶点数据
	vertexDatas.push_back(texCoords);
	//记录步长
	this->stride += 2;
}

//设置顶点索引数据
void InputAssembler::SetVertexIndex(std::vector<unsigned int> &indices)
{
	//记录索引数据
	this->indices = indices;

	//缓存描述信息
	D3D11_BUFFER_DESC bufferDesc;
	//标志缓存用于顶点索引
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//用途是默认用途：GPU可以读写这片缓存
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//CPU不可访问这片内存
	bufferDesc.CPUAccessFlags = 0;
	//不适用其他杂项标志
	bufferDesc.MiscFlags = 0;
	//缓存的大小，以字节为单位
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(unsigned int) * indices.size());
	//每个顶点的大小
	bufferDesc.StructureByteStride = 0;
	//顶点索引缓存实际信息
	D3D11_SUBRESOURCE_DATA sourceData;
	sourceData.pSysMem = this->indices.data();
	//创建顶点索引对象
	DirectX11::GetInstance().pDevice->CreateBuffer(&bufferDesc, &sourceData, &pIndex);
}

//设置绘制的基本图元
void InputAssembler::SetPrimitive(BasicPrimitive basicPrimitive)
{
	//三角形图元
	if (basicPrimitive == BasicPrimitive::Triangle)
		this->basicPrimitive = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

//关联顶点着色器
void InputAssembler::AssociateVertexShader(std::shared_ptr<VertexShader> pVertexShader)
{
	this->pVertexShader = pVertexShader;
}

//设置顶点数据
void InputAssembler::SetVertexData(std::vector<float> data, std::vector<unsigned int> strides, std::vector<std::string> semantics)
{
	//记录每个顶点属性
	for (int i = 0; i < strides.size(); i++)
	{
		//记录顶点步长
		stride += strides[i];

		//顶点输入描述信息
		D3D11_INPUT_ELEMENT_DESC desc;
		//顶点着色器中的语义名字
		desc.SemanticName = semantics[i].c_str();
		//语义索引，当程序中含有相同的语义的时候，我们需要使用语义索引进行区分
		desc.SemanticIndex = 0;
		//传入的数据的类型
		desc.Format = DXGI_FORMAT_R32G32_FLOAT;
		//输入槽编号，
		desc.InputSlot = 0;
		//读取数据的起始位置偏移
		desc.AlignedByteOffset = 0;
		//输入槽中数据的类型
		desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		//实例绘制的个数
		desc.InstanceDataStepRate = 0;

		//记录顶点属性描述
		vertexDescs.push_back(desc);
	}
	//记录顶点数据
	vertexDatas.push_back(data);
}
