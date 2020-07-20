#pragma once
#include <DirectXMath.h>

class MyCamera
{
public:
	MyCamera(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 forward, DirectX::XMFLOAT3 up, DirectX::XMFLOAT3 right);

	//设置投影矩阵的视锥体的相关参数
	void SetFrustum(float fovY, float aspect, float nearZ, float farZ);
	//移动摄像机
	void Move(DirectX::XMFLOAT3 dis);
	//直接设置摄像机的位置
	void SetPosition(DirectX::XMFLOAT3 pos);
	//使用第三人称让摄像机锁定某一个物体
	void Lock(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 distance);

private:
	//观察矩阵
	DirectX::XMFLOAT4X4 view;
	//投影矩阵
	DirectX::XMFLOAT4X4 projection;
	//摄像机位置
	DirectX::XMFLOAT3 position;
	//正前方向
	DirectX::XMFLOAT3 forward;
	//右方向
	DirectX::XMFLOAT3 right;
	//上方向
	DirectX::XMFLOAT3 up;
	//被锁定的目标位置
	DirectX::XMFLOAT3 lockPosition;
	//更新观察矩阵
	void UpdateView();
};

