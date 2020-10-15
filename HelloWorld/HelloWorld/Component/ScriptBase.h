#pragma once
#include "Component.h"

class ScriptBase : public Component
{
public:
	//一开始的逻辑
	virtual void Start(){}
	//每一帧调用的逻辑
	virtual void Update(){}
};
