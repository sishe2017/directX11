#pragma once
#include <memory>
#include <vector>
#include "../DirectX11/InputAssembler.h"
#include "../DirectX11/VertexShader.h"
#include "Component.h"
#include "../Geometry/Matrix4x4.h"

//物体网格
class Mesh : public Component
{
	//friend class Game;
public:
	Mesh();

	//设置顶点数据
	void SetVertexPos(std::vector<float> vertices);
	//设置纹理坐标
	void SetVertexTexCoord(std::vector<float> texCoords);
	//设置顶点索引
	void SetIndex(std::vector<unsigned int> indices);
	//绘制网格
	void Draw();
	//加载顶点着色器
	void LoadVertexShader(std::wstring shaderName);

private:
	//游戏物体的顶点装配器
	std::shared_ptr<InputAssembler> inputAssembler;
	//游戏物体的顶点着色器
	std::shared_ptr<VertexShader> vertexShader;
};