#include "Keyboard.h"

//有按键处于按下状态
bool Keyboard::GetKey(KeyCode keyCode)
{
    return GetInstance().keyStates[static_cast<unsigned int>(keyCode)] == true;
}

//有按键正在被按下
bool Keyboard::GetKeyDown(KeyCode keyCode)
{
    //查看指定键位是否被按下,并且有键落下事件发生
    if (GetInstance().keyStates[static_cast<unsigned int>(keyCode)] &&
        GetInstance().keyDownEvents[static_cast<unsigned int>(keyCode)])
    {
        GetInstance().keyDownEvents[static_cast<unsigned int>(keyCode)] = false;
        return true;
    }

    //如果已经被处理过了，直接返回false
    return false;
}

//有按键正在被弹起
bool Keyboard::GetKeyUp(KeyCode keyCode)
{
    //查看指定键位是否处于弹起状态，并且是否有键弹起的事件发生
    if (!GetInstance().keyStates[static_cast<unsigned int>(keyCode)] && 
        GetInstance().keyUpEvents[static_cast<unsigned int>(keyCode)])
    {
        GetInstance().keyUpEvents[static_cast<unsigned int>(keyCode)] = false;
        return true;
    }

    //如果没有处理，直接返回false
    return false;
}

Keyboard& Keyboard::GetInstance()
{
    static Keyboard keyboard;
    return keyboard;
}

//当键盘有键落下的事件处理
void Keyboard::OnKeyDown(unsigned int keycode)
{
    //如果当前按键正在处于按下状态，直接返回
    if (GetInstance().keyStates[keycode] == true)
        return;

    //设置按键情况表和按键按下事件表
    GetInstance().keyStates[keycode] = true;
    GetInstance().keyDownEvents[keycode] = true;
}

//当键盘有键弹起的事件处理
void Keyboard::OnKeyUp(unsigned int keycode)
{
    //设置按键情况表和按键按下事件表
    GetInstance().keyStates[keycode] = false;
    GetInstance().keyUpEvents[keycode] = true;
}
