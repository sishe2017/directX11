#include "Keyboard.h"

//�а������ڰ���״̬
bool Keyboard::GetKey(KeyCode keyCode)
{
    return GetInstance().keyStates[static_cast<unsigned int>(keyCode)] == true;
}

//�а������ڱ�����
bool Keyboard::GetKeyDown(KeyCode keyCode)
{
    //�鿴ָ����λ�Ƿ񱻰���,�����м������¼�����
    if (GetInstance().keyStates[static_cast<unsigned int>(keyCode)] &&
        GetInstance().keyDownEvents[static_cast<unsigned int>(keyCode)])
    {
        GetInstance().keyDownEvents[static_cast<unsigned int>(keyCode)] = false;
        return true;
    }

    //����Ѿ���������ˣ�ֱ�ӷ���false
    return false;
}

//�а������ڱ�����
bool Keyboard::GetKeyUp(KeyCode keyCode)
{
    //�鿴ָ����λ�Ƿ��ڵ���״̬�������Ƿ��м�������¼�����
    if (!GetInstance().keyStates[static_cast<unsigned int>(keyCode)] && 
        GetInstance().keyUpEvents[static_cast<unsigned int>(keyCode)])
    {
        GetInstance().keyUpEvents[static_cast<unsigned int>(keyCode)] = false;
        return true;
    }

    //���û�д���ֱ�ӷ���false
    return false;
}

Keyboard& Keyboard::GetInstance()
{
    static Keyboard keyboard;
    return keyboard;
}

//�������м����µ��¼�����
void Keyboard::OnKeyDown(unsigned int keycode)
{
    //�����ǰ�������ڴ��ڰ���״̬��ֱ�ӷ���
    if (GetInstance().keyStates[keycode] == true)
        return;

    //���ð��������Ͱ��������¼���
    GetInstance().keyStates[keycode] = true;
    GetInstance().keyDownEvents[keycode] = true;
}

//�������м�������¼�����
void Keyboard::OnKeyUp(unsigned int keycode)
{
    //���ð��������Ͱ��������¼���
    GetInstance().keyStates[keycode] = false;
    GetInstance().keyUpEvents[keycode] = true;
}
