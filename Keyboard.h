#pragma once
#include <bitset>

//键盘按键
enum class KeyCode
{
	//26个英文字符
	A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N,
	O, P, Q, R, S, T, U, V, W, X, Y, Z,
	//空格和回车,ecs
	Space = 32, Enter = 13, ESC = 27,
	//键盘顶部数字键
	Alpha0 = 48, Alpha1, Alpha2, Alpha3, Alpha4, Alpha5,
	Alpha6, Alpha7, Alpha8, Alpha9, 
	//F1~F12
	F1 = 112, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
};

class Keyboard
{
	friend class Window;
public:
	//有按键处于按下状态
	static bool GetKey(KeyCode keyCode);
	//有按键正在被按下
	static bool GetKeyDown(KeyCode keyCode);
	//有按键正在被弹起
	static bool GetKeyUp(KeyCode keyCode);

private:
	//单例模式
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;
	static Keyboard& GetInstance();

	//按键情况表（统计键盘是否被按下，0表示未被按下，1表示按下）
	std::bitset<256> keyStates;
	//键盘按下事件表
	std::bitset<256> keyDownEvents;
	//键盘弹起事件表
	std::bitset<256> keyUpEvents;

	//键盘有键落下的事件处理
	static void OnKeyDown(unsigned int keycode);
	//键盘有键弹起的事件处理
	static void OnKeyUp(unsigned int keycode);
};
