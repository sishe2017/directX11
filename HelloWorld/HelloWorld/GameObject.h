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

	//transform���ָ��
	std::shared_ptr<Transform> transform;

	//���������Դ��Ļ���ͼ��
	static std::shared_ptr<GameObject> CreatePrimitive(PrimitiveType primitiveType);

	//������
	void AddComponent(std::shared_ptr<Component> component);

private:
	//��Ϸ������������
	std::vector<std::shared_ptr<Component>> components;

	//���ƺ���
	void Draw();
};

