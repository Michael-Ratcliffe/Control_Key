#ifdef _WIN32
#include "windowsplatform.h"

WindowsPlatform::WindowsPlatform()
{
    //Keyboard scancodes
    //Located from: https://msdn.microsoft.com/en-us/library/aa299374%28v=vs.60%29.aspx
    _AddInput("a", Input(30, INPUT_KEYBOARDBUTTON));
    _AddInput("b", Input(48, INPUT_KEYBOARDBUTTON));
    _AddInput("c", Input(46, INPUT_KEYBOARDBUTTON));
    _AddInput("d", Input(32, INPUT_KEYBOARDBUTTON));
    _AddInput("e", Input(18, INPUT_KEYBOARDBUTTON));
    _AddInput("f", Input(33, INPUT_KEYBOARDBUTTON));
    _AddInput("g", Input(34, INPUT_KEYBOARDBUTTON));
    _AddInput("h", Input(35, INPUT_KEYBOARDBUTTON));
    _AddInput("i", Input(23, INPUT_KEYBOARDBUTTON));
    _AddInput("j", Input(36, INPUT_KEYBOARDBUTTON));
    _AddInput("k", Input(37, INPUT_KEYBOARDBUTTON));
    _AddInput("l", Input(38, INPUT_KEYBOARDBUTTON));
    _AddInput("m", Input(50, INPUT_KEYBOARDBUTTON));
    _AddInput("n", Input(49, INPUT_KEYBOARDBUTTON));
    _AddInput("o", Input(24, INPUT_KEYBOARDBUTTON));
    _AddInput("p", Input(25, INPUT_KEYBOARDBUTTON));
    _AddInput("q", Input(16, INPUT_KEYBOARDBUTTON));
    _AddInput("r", Input(19, INPUT_KEYBOARDBUTTON));
    _AddInput("s", Input(31, INPUT_KEYBOARDBUTTON));
    _AddInput("t", Input(20, INPUT_KEYBOARDBUTTON));
    _AddInput("u", Input(22, INPUT_KEYBOARDBUTTON));
    _AddInput("v", Input(47, INPUT_KEYBOARDBUTTON));
    _AddInput("w", Input(17, INPUT_KEYBOARDBUTTON));
    _AddInput("x", Input(45, INPUT_KEYBOARDBUTTON));
    _AddInput("y", Input(21, INPUT_KEYBOARDBUTTON));
    _AddInput("z", Input(44, INPUT_KEYBOARDBUTTON));

    _AddInput("f1", Input(59, INPUT_KEYBOARDBUTTON));
    _AddInput("f2", Input(60, INPUT_KEYBOARDBUTTON));
    _AddInput("f3", Input(61, INPUT_KEYBOARDBUTTON));
    _AddInput("f4", Input(62, INPUT_KEYBOARDBUTTON));
    _AddInput("f5", Input(63, INPUT_KEYBOARDBUTTON));
    _AddInput("f6", Input(64, INPUT_KEYBOARDBUTTON));
    _AddInput("f7", Input(65, INPUT_KEYBOARDBUTTON));
    _AddInput("f8", Input(66, INPUT_KEYBOARDBUTTON));
    _AddInput("f9", Input(67, INPUT_KEYBOARDBUTTON));
    _AddInput("f10", Input(68, INPUT_KEYBOARDBUTTON));
    _AddInput("f11", Input(133, INPUT_KEYBOARDBUTTON));
    _AddInput("f12", Input(134, INPUT_KEYBOARDBUTTON));

    _AddInput("escape", Input(1, INPUT_KEYBOARDBUTTON));
    _AddInput("tab", Input(15, INPUT_KEYBOARDBUTTON));
    _AddInput("shift", Input(42, INPUT_KEYBOARDBUTTON));
    _AddInput("enter", Input(28, INPUT_KEYBOARDBUTTON));
    _AddInput("space", Input(57, INPUT_KEYBOARDBUTTON));
    _AddInput("backspace", Input(14, INPUT_KEYBOARDBUTTON));
    _AddInput("control", Input(29, INPUT_KEYBOARDBUTTON));
    _AddInput("alt", Input(56, INPUT_KEYBOARDBUTTON));

    //Mouse
    _AddInput("leftclick", Input(MOUSEEVENTF_LEFTDOWN, INPUT_MOUSEBUTTON));
    _AddInput("middleclick", Input(MOUSEEVENTF_MIDDLEDOWN, INPUT_MOUSEBUTTON));
    _AddInput("rightclick", Input(MOUSEEVENTF_RIGHTDOWN, INPUT_MOUSEBUTTON));
    _AddInput("scrollup", Input(1, INPUT_MOUSEWHEEL));
    _AddInput("scrolldown", Input(-1, INPUT_MOUSEWHEEL));
}

std::string WindowsPlatform::GetOSName()const
{
    //TODO: provide more useful information
    return "Windows";
}

void WindowsPlatform::_OSFakeKeyPress(int keycode, bool pressed)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = keycode; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = 0; //keycode;

    if(pressed)
    {
        ip.ki.dwFlags = 0 | KEYEVENTF_SCANCODE; // 0 for key press
    }
    else
        ip.ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_SCANCODE;

    SendInput(1, &ip, sizeof(INPUT));
}

void WindowsPlatform::_OSFakeMouseMove(int x, int y)
{
    INPUT ip;
    ip.type = INPUT_MOUSE;
    ip.mi.mouseData = 0;
    ip.mi.time = 0;
    ip.mi.dwExtraInfo = 0;
    ip.mi.dx = x;
    ip.mi.dy = y;
    ip.mi.dwFlags = MOUSEEVENTF_MOVE;

    SendInput(1, &ip, sizeof(INPUT));
}

void WindowsPlatform::_OSFakeMouseButton(int button, bool pressed)
{
    INPUT ip;
    ip.type = INPUT_MOUSE;
    ip.mi.mouseData = 0;
    ip.mi.time = 0;
    ip.mi.dwExtraInfo = 0;
    ip.mi.dx = 0;
    ip.mi.dy = 0;

    if(pressed)
        ip.mi.dwFlags = button;
    else
        ip.mi.dwFlags = button*2;//the button code *2 is its release state

    SendInput(1, &ip, sizeof(INPUT));
}

void WindowsPlatform::_OSFakeMouseWheel(int direction, bool pressed)
{
    INPUT ip;
    ip.type = INPUT_MOUSE;
    ip.mi.time = 0;
    ip.mi.dwExtraInfo = 0;
    ip.mi.dx = 0;
    ip.mi.dy = 0;
    ip.mi.dwFlags = MOUSEEVENTF_WHEEL;

    if(doubleScroll)
        ip.mi.mouseData = 2*((WHEEL_DELTA*direction)*(int)pressed);
    else
        ip.mi.mouseData = (WHEEL_DELTA*direction)*(int)pressed;

    SendInput(1, &ip, sizeof(INPUT));
}

WindowsPlatform::~WindowsPlatform()
{
    ClearEvents();
}

#endif
