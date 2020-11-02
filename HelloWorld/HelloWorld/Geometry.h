#pragma once
#include <vector>


//����λ�ú������ṹ
class VertexInfo
{
public:
	VertexInfo(std::vector<float> vertices, std::vector<float> texCoords, std::vector<unsigned int> indices) :
		pos(vertices),
		texCoords(texCoords),
		indices(indices) {}

	//λ��
	std::vector<float> pos;
	//��������
	std::vector<float> texCoords;
	//����
	std::vector<unsigned int> indices;
};

//������������
class Geometry
{
public:
	static VertexInfo boxInfo;
};