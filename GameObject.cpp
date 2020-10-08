#include "GameObject.h"
#include "DirectX11Pipeline.h"
#include "Mesh.h"
#include "Geometry.h"
#include "ShadowEngine.h"
#include "Material.h"

using namespace std;

GameObject::GameObject()
{

}

//���������Դ��Ļ�������
std::shared_ptr<GameObject> GameObject::CreatePrimitive(PrimitiveType primitiveType)
{
	//����һ����Ϸ����
	shared_ptr<GameObject> gameObject(new GameObject);
	//���������Դ�Transform���
	gameObject->transform = make_shared<Transform>();
	gameObject->transform->position = Vector3();
	//��¼Transform���
	gameObject->AddComponent(gameObject->transform);
	//gameObject->transform->gameObject = gameObject;
	
	//����ö�����ʹ�����Ϸ����
	if (primitiveType == PrimitiveType::Cube)
	{
		//��������
		auto mesh = make_shared<Mesh>();
		mesh->SetVertices(Geometry::boxInfo.vertices);
		mesh->SetIndex(Geometry::boxInfo.indices);
		mesh->LoadVertexShader(L"CubeVS.cso");
		gameObject->AddComponent(mesh);
		//���ò���
		auto material = make_shared<Material>();
		//�����������ɫ
		std::vector<float> colors =
		{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 0.0f,
		};
		material->pixelShader->SetConstant(colors, 0);
		material->LoadPixelShader(L"CubePS.cso");
		gameObject->AddComponent(material);
	}

	return gameObject;
}

//������
void GameObject::AddComponent(std::shared_ptr<Component> component)
{
	components.push_back(component);
	component->gameObject = shared_from_this();
}

void GameObject::Draw()
{
	for (int i = 0; i < components.size(); i++)
	{
		//�������Mesh��������������Ļ��� 
		if (typeid(*components[i]) == typeid(Mesh))
		{
			dynamic_pointer_cast<Mesh>(components[i])->Draw();
		}
		//�������Matrila���������в��ʵĻ���
		else if (typeid(*components[i]) == typeid(Material))
		{
			dynamic_pointer_cast<Material>(components[i])->Draw();
		}
	}
}
