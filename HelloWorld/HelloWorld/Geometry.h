#pragma once
#include <vector>


//顶点位置和索引结构
class VertexInfo
{
public:
	VertexInfo(std::vector<float> vertices, std::vector<float> texCoords, std::vector<unsigned int> indices) :
		pos(vertices),
		texCoords(texCoords),
		indices(indices) {}

	//位置
	std::vector<float> pos;
	//纹理坐标
	std::vector<float> texCoords;
	//索引
	std::vector<unsigned int> indices;
};

//几何物体数据
class Geometry
{
public:
	static VertexInfo boxInfo;
};