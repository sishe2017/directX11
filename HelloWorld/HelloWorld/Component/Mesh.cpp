#include "Mesh.h"
#include "../GameObject.h"
#include "../DirectX11Pipeline.h"

using namespace std;

Mesh::Mesh()
{
	//��������װ����
	inputAssembler = make_shared<InputAssembler>();
	//���ƵĻ���ͼԪ����Ϊ������
	inputAssembler->SetPrimitive(BasicPrimitive::Triangle);
	
	//����������ɫ��
	vertexShader = make_shared<VertexShader>();
}

//���ö�������
void Mesh::SetVertices(std::vector<float> vertices)
{
	inputAssembler->SetVertexPos(vertices);
}

//���ö�������
void Mesh::SetIndex(std::vector<unsigned int> indices)
{
	inputAssembler->SetVertexIndex(indices);
}

//������
void Mesh::Draw()
{
	//������װ�����Ͷ�����ɫ��������ˮ��
	DirectX11Pipeline::BindInputAssembler(inputAssembler);
	DirectX11Pipeline::BindVertexShader(vertexShader);
	//���ó���
	vertexShader->SetConstant(
		Matrix4x4::Transpose(gameObject->transform->model * Matrix4x4::Perspective(1.0, 3.0f / 4.0f, 0.5f, 100.0f)), 0);
}

//���ض�����ɫ��
void Mesh::LoadVertexShader(std::wstring path)
{
	//����װ����������ϵ��VS
	inputAssembler->AssociateVertexShader(path);
	//������ɫ������VS����
	vertexShader->Load(path);
}
