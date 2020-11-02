#pragma once
#include <memory>
#include <vector>
#include "../DirectX11/InputAssembler.h"
#include "../DirectX11/VertexShader.h"
#include "Component.h"
#include "../Geometry/Matrix4x4.h"

//��������
class Mesh : public Component
{
	//friend class Game;
public:
	Mesh();

	//���ö�������
	void SetVertexPos(std::vector<float> vertices);
	//������������
	void SetVertexTexCoord(std::vector<float> texCoords);
	//���ö�������
	void SetIndex(std::vector<unsigned int> indices);
	//��������
	void Draw();
	//���ض�����ɫ��
	void LoadVertexShader(std::wstring shaderName);

private:
	//��Ϸ����Ķ���װ����
	std::shared_ptr<InputAssembler> inputAssembler;
	//��Ϸ����Ķ�����ɫ��
	std::shared_ptr<VertexShader> vertexShader;
};