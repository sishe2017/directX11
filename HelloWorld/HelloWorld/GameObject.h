#pragma once
#include <vector>
#include <memory>
#include "Component/Component.h"
#include "DirectX11/InputAssembler.h"
#include "DirectX11/VertexShader.h"
#include "DirectX11/PixelShader.h"
#include "Component/Transform.h"
#include "Type.h"


class GameObject : public std::enable_shared_from_this<GameObject>
{
	friend class ShadowEngine;
public:
	GameObject();

	//transform组件指针
	std::shared_ptr<Transform> transform;

	//创建引擎自带的基本图形
	static std::shared_ptr<GameObject> CreatePrimitive(PrimitiveType primitiveType);

	//添加组件
	void AddComponent(std::shared_ptr<Component> component);

private:
	//游戏物体的组件集合
	std::vector<std::shared_ptr<Component>> components;

	//绘制函数
	void Draw();
};

