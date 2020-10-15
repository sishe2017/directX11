#include "Mesh.h"
#include "../GameObject.h"
#include "../DirectX11Pipeline.h"

using namespace std;

Mesh::Mesh()
{
	//创建输入装配器
	inputAssembler = make_shared<InputAssembler>();
	//绘制的基本图元设置为三角形
	inputAssembler->SetPrimitive(BasicPrimitive::Triangle);
	
	//创建顶点着色器
	vertexShader = make_shared<VertexShader>();
}

//设置顶点数据
void Mesh::SetVertices(std::vector<float> vertices)
{
	inputAssembler->SetVertexPos(vertices);
}

//设置顶点索引
void Mesh::SetIndex(std::vector<unsigned int> indices)
{
	inputAssembler->SetVertexIndex(indices);
}

//绑定网格
void Mesh::Draw()
{
	//将输入装配器和顶点着色器绑定至流水线
	DirectX11Pipeline::BindInputAssembler(inputAssembler);
	DirectX11Pipeline::BindVertexShader(vertexShader);
	//设置常量
	vertexShader->SetConstant(
		Matrix4x4::Transpose(gameObject->transform->model * Matrix4x4::Perspective(1.0, 3.0f / 4.0f, 0.5f, 100.0f)), 0);
}

//加载顶点着色器
void Mesh::LoadVertexShader(std::wstring path)
{
	//顶点装配器设置联系的VS
	inputAssembler->AssociateVertexShader(path);
	//顶点着色器加载VS代码
	vertexShader->Load(path);
}
