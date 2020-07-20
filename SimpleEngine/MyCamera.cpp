#include "MyCamera.h"

using namespace DirectX;

MyCamera::MyCamera(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 forward, DirectX::XMFLOAT3 up, DirectX::XMFLOAT3 right):
position(pos),
forward(forward),
up(up),
right(right)
{
}

void MyCamera::SetFrustum(float fovY, float aspect, float nearZ, float farZ)
{
	XMStoreFloat4x4(&projection, XMMatrixPerspectiveFovLH(fovY, aspect, nearZ, farZ));
}

void MyCamera::Move(DirectX::XMFLOAT3 dis)
{
	//¸üÐÂÎ»ÖÃ
	position.x += dis.x;
	position.y += dis.y;
	position.z += dis.z;


}

void MyCamera::UpdateView()
{
	view = {
	right.x, up.x, forward.x, 0.0f,
	right.y, up.y, forward.y, 0.0f,
	right.z, up.z, forward.z, 0.0f,
	-position.x, -position.y, -position.z, 1.0f
	};
}
