#include "Mesh.h"
#include "../GameObject.h"
#include "../DirectX11Pipeline.h"
#include "../ShaderTable.h"

using namespace std;

Mesh::Mesh()
{
	//创建输入装配器
	inputAssembler = make_shared<InputAssembler>();
	//绘制的基本图元设置为三角形
	inputAssembler->SetPrimitive(BasicPrimitive::Triangle);
}

//设置顶点数据
void Mesh::SetVertexPos(std::vector<float> vertices)
{
	inputAssembler->SetVertexPos(vertices);
}

//设置纹理坐标
void Mesh::SetVertexTexCoord(std::vector<float> texCoords)
{
	inputAssembler->SetVertexTexCoord(texCoords);
}

//设置顶点索引
void Mesh::SetIndex(std::vector<unsigned int> indices)
{
	inputAssembler->SetVertexIndex(indices);
	//提交数据
	inputAssembler->CommitVertexData();
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
void Mesh::LoadVertexShader(std::wstring shaderName)
{
	//获取顶点着色器
	this->vertexShader = ShaderTable::GetVertexShader(shaderName);
	//设置顶点装配器联系的VS
	inputAssembler->AssociateVertexShader(this->vertexShader);
}
