#pragma once
#include <bitset>
#include "Vector2.h"

enum class MouseButton
{
	//左键
	LeftButton = 0,
	//右键
	RightButton
};

//鼠标类
class Mouse
{
	friend class Window;
public:
	//鼠标有键按下
	static bool GetMouseButtonDown(MouseButton mouseButton);
	//鼠标有键输入
	static bool GetMouseButton(MouseButton mouseButton);
	//鼠标有键弹起
	static bool GetMouseButtonUp(MouseButton mouseButton);

	//鼠标位置
	static Vector2 mousePosition;

private:
	//单例模式
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	static Mouse& GetInstance();

	//鼠标按键的状态
	std::bitset<2> keyStates;
	//鼠标按键落下的事件标志
	std::bitset<2> keyDownEvents;
	//鼠标按键弹起的事件标志
	std::bitset<2> keyUpEvents;

	//鼠标键落下的事件处理
	static void OnKeyDown(unsigned int keycode);
	//鼠标键弹起的事件处理
	static void OnKeyUp(unsigned int keycode);
	//鼠标移动的事件处理
	static void OnMouseMove(int x, int y);
};

