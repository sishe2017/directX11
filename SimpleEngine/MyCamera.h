#pragma once
#include <DirectXMath.h>

class MyCamera
{
public:
	MyCamera(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 forward, DirectX::XMFLOAT3 up, DirectX::XMFLOAT3 right);

	//����ͶӰ�������׶�����ز���
	void SetFrustum(float fovY, float aspect, float nearZ, float farZ);
	//�ƶ������
	void Move(DirectX::XMFLOAT3 dis);
	//ֱ�������������λ��
	void SetPosition(DirectX::XMFLOAT3 pos);
	//ʹ�õ����˳������������ĳһ������
	void Lock(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 distance);

private:
	//�۲����
	DirectX::XMFLOAT4X4 view;
	//ͶӰ����
	DirectX::XMFLOAT4X4 projection;
	//�����λ��
	DirectX::XMFLOAT3 position;
	//��ǰ����
	DirectX::XMFLOAT3 forward;
	//�ҷ���
	DirectX::XMFLOAT3 right;
	//�Ϸ���
	DirectX::XMFLOAT3 up;
	//��������Ŀ��λ��
	DirectX::XMFLOAT3 lockPosition;
	//���¹۲����
	void UpdateView();
};

