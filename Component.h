#pragma once
#include <memory>

class GameObject;

class Component
{
	friend class GameObject;
public:
	virtual ~Component();

	//ӵ���������Ϸ����
	std::shared_ptr<GameObject> gameObject;
};

