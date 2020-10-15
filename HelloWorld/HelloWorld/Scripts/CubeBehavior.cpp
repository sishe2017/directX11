#include "CubeBehavior.h"
#include "../GameObject.h"
#include "../Time.h"
#include "../Geometry/Vector3.h"

void CubeBehavior::Start()
{
}

void CubeBehavior::Update()
{
	gameObject->transform->Rotate(Vector3(Time::deltaTime, Time::deltaTime, Time::deltaTime));
}
