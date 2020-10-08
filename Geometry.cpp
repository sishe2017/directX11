#include "Geometry.h"


//立方体顶点数据
std::vector<unsigned int> boxIndieces{
	1, 0, 2, 1, 2, 3,
	4, 0, 1, 4, 1, 5,
	1, 3, 5, 3, 7, 5,
	0, 4, 6, 0, 6, 2,
	4, 5, 6, 5, 7, 6,
	3, 6, 7, 2, 6, 3
};
std::vector<float> boxVertices
{
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
};
VertexInfo Geometry::boxInfo(boxVertices, boxIndieces);
