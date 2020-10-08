#pragma once
#include <memory>

class GameObject;

class Component
{
	friend class GameObject;
public:
	virtual ~Component();

	//拥有组件的游戏物体
	std::shared_ptr<GameObject> gameObject;
};

