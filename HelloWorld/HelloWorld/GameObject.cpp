#include "GameObject.h"
#include "DirectX11Pipeline.h"
#include "Component/Mesh.h"
#include "Geometry.h"
#include "ShadowEngine.h"
#include "Component/Material.h"

using namespace std;

GameObject::GameObject()
{

}

//创建引擎自带的基本物体
std::shared_ptr<GameObject> GameObject::CreatePrimitive(PrimitiveType primitiveType)
{
	//创建一个游戏物体
	auto gameObject = make_shared<GameObject>();
	//基本物体自带Transform组件
	gameObject->transform = make_shared<Transform>();
	gameObject->transform->SetPosition(Vector3());
	//记录Transform组件
	gameObject->AddComponent(gameObject->transform);
	
	//根据枚举类型创建游戏物体
	if (primitiveType == PrimitiveType::Cube)
	{
		//设置网格
		auto mesh = make_shared<Mesh>();
		//设置网格的顶点数据
		mesh->SetVertexPos(Geometry::boxInfo.pos);
		mesh->SetVertexTexCoord(Geometry::boxInfo.texCoords);
		mesh->SetIndex(Geometry::boxInfo.indices);
		mesh->LoadVertexShader(L"CubeVS");
		gameObject->AddComponent(mesh);
		//设置材质
		auto material = make_shared<Material>();
		material->LoadPixelShader(L"CubePS");
		material->LoadTexture(L"Images/kappa50.png");
		gameObject->AddComponent(material);
	}

	return gameObject;
}

//添加组件
void GameObject::AddComponent(std::shared_ptr<Component> component)
{
	components.push_back(component);
	component->gameObject = shared_from_this();
}

void GameObject::Draw()
{
	for (int i = 0; i < components.size(); i++)
	{
		//如果存在Mesh组件，则进行网格的绘制 
		if (typeid(*components[i]) == typeid(Mesh))
		{
			dynamic_pointer_cast<Mesh>(components[i])->Draw();
		}
		//如果存在Matrila组件，则进行材质的绘制
		else if (typeid(*components[i]) == typeid(Material))
		{
			dynamic_pointer_cast<Material>(components[i])->Draw();
		}
	}

	//调用DirectX11接口进行绘制
	DirectX11::Draw();
}
