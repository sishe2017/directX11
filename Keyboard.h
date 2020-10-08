#pragma once
#include <bitset>

//���̰���
enum class KeyCode
{
	//26��Ӣ���ַ�
	A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N,
	O, P, Q, R, S, T, U, V, W, X, Y, Z,
	//�ո�ͻس�,ecs
	Space = 32, Enter = 13, ESC = 27,
	//���̶������ּ�
	Alpha0 = 48, Alpha1, Alpha2, Alpha3, Alpha4, Alpha5,
	Alpha6, Alpha7, Alpha8, Alpha9, 
	//F1~F12
	F1 = 112, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
};

class Keyboard
{
	friend class Window;
public:
	//�а������ڰ���״̬
	static bool GetKey(KeyCode keyCode);
	//�а������ڱ�����
	static bool GetKeyDown(KeyCode keyCode);
	//�а������ڱ�����
	static bool GetKeyUp(KeyCode keyCode);

private:
	//����ģʽ
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;
	static Keyboard& GetInstance();

	//���������ͳ�Ƽ����Ƿ񱻰��£�0��ʾδ�����£�1��ʾ���£�
	std::bitset<256> keyStates;
	//���̰����¼���
	std::bitset<256> keyDownEvents;
	//���̵����¼���
	std::bitset<256> keyUpEvents;

	//�����м����µ��¼�����
	static void OnKeyDown(unsigned int keycode);
	//�����м�������¼�����
	static void OnKeyUp(unsigned int keycode);
};
