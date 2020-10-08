#include "InputAssembler.h"
#include "DirectX11.h"

using namespace Microsoft::WRL;

//绑定输入装配阶段
void InputAssembler::Bind()
{
	//顶点着色器未关联直接抛出异常
	if (!pVertexShader)
		throw "vertex not associate";
	//创建顶点布局
	DirectX11::GetInstance().pDevice->CreateInputLayout(
		vertexProperties.data(), UINT(vertexProperties.size()), pVertexShader->GetBufferPointer(),
		pVertexShader->GetBufferSize(), &pInputLayout);
	//绑定顶点位置布局
	DirectX11::GetInstance().pContext->IASetInputLayout(this->pInputLayout.Get());
	//绑定顶点缓存
	DirectX11::GetInstance().pContext->IASetVertexBuffers(
		0, 1, vertexPosition.pVertex.GetAddressOf(), &(vertexPosition.stride), &(vertexPosition.offset));
	//绑定顶点索引缓存
	DirectX11::GetInstance().pContext->IASetIndexBuffer(pIndex.Get(), DXGI_FORMAT_R32_UINT, 0);
	//设置图元装配的目标图元
	DirectX11::GetInstance().pContext->IASetPrimitiveTopology(this->basicPrimitive);
}

//设置顶点位置数据
void InputAssembler::SetVertexPos(std::vector<float> vertices, UINT stride, UINT offset)
{
	//设置顶点位置的步长和偏移
	vertexPosition.stride = stride;
	vertexPosition.offset = offset;
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
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(float) * vertices.size());
	//每个顶点的大小
	// todo:目前没看到这个属性的作用
	bufferDesc.StructureByteStride = 0;
	//设置常量缓存存储的数据
	D3D11_SUBRESOURCE_DATA sourceData;
	sourceData.pSysMem = vertices.data();
	//创建顶点位置缓存对象
	DirectX11::GetInstance().pDevice->CreateBuffer(&bufferDesc, &sourceData, &(vertexPosition.pVertex));

	//顶点位置信息描述
	D3D11_INPUT_ELEMENT_DESC posDesc;
	//顶点着色器中的位置的语义名字
	posDesc.SemanticName = "POSITION";
	//语义索引，当程序中含有相同的语义的时候，我们需要使用语义索引进行区分
	posDesc.SemanticIndex = 0;
	//传入的数据的类型
	posDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	//输入槽编号，
	posDesc.InputSlot = 0;
	//读取数据的起始位置偏移
	posDesc.AlignedByteOffset = 0;
	//输入槽中数据的类型
	posDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	//实例绘制的个数
	posDesc.InstanceDataStepRate = 0;

	//记录顶点属性描述
	vertexProperties.push_back(posDesc);
}

//设置顶点索引数据
void InputAssembler::SetVertexIndex(std::vector<unsigned int> indices)
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
void InputAssembler::AssociateVertexShader(std::wstring path)
{
	D3DReadFileToBlob(L"VertexShader.cso", &pVertexShader);
}
