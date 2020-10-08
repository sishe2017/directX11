#include "Mouse.h"
#include "Log.h"

using namespace std;

//��ʼ����̬����
Vector2 Mouse::mousePosition;

//����м�����
bool Mouse::GetMouseButtonDown(MouseButton mouseButton)
{
    //�������Ӧ�������ڰ���״̬�������м����µ��¼�����,����true
    if (GetInstance().keyStates[static_cast<unsigned int>(mouseButton)] == true &&
        GetInstance().keyDownEvents[static_cast<unsigned int>(mouseButton)] == true)
    {
        GetInstance().keyDownEvents[static_cast<unsigned int>(mouseButton)] = false;
        return true;
    }

    return false;
}

//����м�����
bool Mouse::GetMouseButton(MouseButton mouseButton)
{
    return GetInstance().keyStates[static_cast<unsigned int>(mouseButton)] == true;
}

//����м�����
bool Mouse::GetMouseButtonUp(MouseButton mouseButton)
{
    //�������Ӧ�������ڰ���״̬�������м�������¼�����,����true
    if (GetInstance().keyStates[static_cast<unsigned int>(mouseButton)] == false &&
        GetInstance().keyUpEvents[static_cast<unsigned int>(mouseButton)] == true)
    {
        GetInstance().keyUpEvents[static_cast<unsigned int>(mouseButton)] = false;
        return true;
    }

    return false;
}

Mouse& Mouse::GetInstance()
{
    static Mouse mouse;
    return mouse;
}

//�������м����µ��¼�����
void Mouse::OnKeyDown(unsigned int keycode)
{
    //��������λ�ͼ������¼���־
    GetInstance().keyStates[keycode] = true;
    GetInstance().keyDownEvents[keycode] = true;
}

//�������м�������¼�����
void Mouse::OnKeyUp(unsigned int keycode)
{
    //��������λ�ͼ������¼���־
    GetInstance().keyStates[keycode] = false;
    GetInstance().keyUpEvents[keycode] = true;
}

//����ƶ����¼�����
void Mouse::OnMouseMove(int x, int y)
{
    //�������λ��
    GetInstance().mousePosition.x = static_cast<float>(x);
    GetInstance().mousePosition.y = static_cast<float>(y);
}
