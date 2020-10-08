#pragma once
#include <bitset>
#include "Vector2.h"

enum class MouseButton
{
	//���
	LeftButton = 0,
	//�Ҽ�
	RightButton
};

//�����
class Mouse
{
	friend class Window;
public:
	//����м�����
	static bool GetMouseButtonDown(MouseButton mouseButton);
	//����м�����
	static bool GetMouseButton(MouseButton mouseButton);
	//����м�����
	static bool GetMouseButtonUp(MouseButton mouseButton);

	//���λ��
	static Vector2 mousePosition;

private:
	//����ģʽ
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	static Mouse& GetInstance();

	//��갴����״̬
	std::bitset<2> keyStates;
	//��갴�����µ��¼���־
	std::bitset<2> keyDownEvents;
	//��갴��������¼���־
	std::bitset<2> keyUpEvents;

	//�������µ��¼�����
	static void OnKeyDown(unsigned int keycode);
	//����������¼�����
	static void OnKeyUp(unsigned int keycode);
	//����ƶ����¼�����
	static void OnMouseMove(int x, int y);
};

