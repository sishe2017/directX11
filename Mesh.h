#pragma once
#include <memory>
#include <vector>
#include "InputAssembler.h"
#include "VertexShader.h"
#include "Component.h"
#include "Matrix4x4.h"

//��������
class Mesh : public Component
{
	//friend class Game;
public:
	Mesh();

	//���ö�������
	void SetVertices(std::vector<float> vertices);
	//���ö�������
	void SetIndex(std::vector<unsigned int> indices);
	//��������
	void Draw();
	//���ض�����ɫ��
	void LoadVertexShader(std::wstring path);

private:
	//��Ϸ����Ķ���װ����
	std::shared_ptr<InputAssembler> inputAssembler;
	//��Ϸ����Ķ�����ɫ��
	std::shared_ptr<VertexShader> vertexShader;
};