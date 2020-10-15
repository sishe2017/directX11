#pragma once
#include <vector>


//����λ�ú������ṹ
class VertexInfo
{
public:
	VertexInfo(std::vector<float> vertices, std::vector<unsigned int> indices) :
		vertices(vertices),
		indices(indices) {}

	//λ��
	std::vector<float> vertices;
	//����
	std::vector<unsigned int> indices;
};

//������������
class Geometry
{
public:
	static VertexInfo boxInfo;
};