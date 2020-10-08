#include "Transform.h"

Transform::Transform()
{
	
}

//����λ��
void Transform::SetPosition(Vector3 pos)
{
	//���㵱ǰλ�õ�Ŀ��λ�õľ���
	auto distance = pos - this->position;
	//ƽ�ƾ���
	Translate(distance);
}

//ƽ��
void Transform::Translate(Vector3 delta)
{
	//����λ��
	position += delta;
	//���±任����
	model *= Matrix4x4::Translation(delta);
}

//��ת
void Transform::Rotate(Vector3 angle)
{
	//���±任����
	model *= Matrix4x4::Rotation(angle);
}
