#ifdef __MACH__
#include "macplatform.h"

//All code here is preliminary and does NOT work yet.

MacPlatform::MacPlatform()
{
    //TODO: Fill in proper scancodes
    /*
    //Keyboard
    _AddInput("a", Input(38, INPUT_KEYBOARDBUTTON));
    _AddInput("b", Input(56, INPUT_KEYBOARDBUTTON));
    _AddInput("c", Input(54, INPUT_KEYBOARDBUTTON));
    _AddInput("d", Input(40, INPUT_KEYBOARDBUTTON));
    _AddInput("e", Input(26, INPUT_KEYBOARDBUTTON));
    _AddInput("f", Input(41, INPUT_KEYBOARDBUTTON));
    _AddInput("g", Input(42, INPUT_KEYBOARDBUTTON));
    _AddInput("h", Input(43, INPUT_KEYBOARDBUTTON));
    _AddInput("i", Input(31, INPUT_KEYBOARDBUTTON));
    _AddInput("j", Input(44, INPUT_KEYBOARDBUTTON));
    _AddInput("k", Input(45, INPUT_KEYBOARDBUTTON));
    _AddInput("l", Input(46, INPUT_KEYBOARDBUTTON));
    _AddInput("m", Input(58, INPUT_KEYBOARDBUTTON));
    _AddInput("n", Input(57, INPUT_KEYBOARDBUTTON));
    _AddInput("o", Input(32, INPUT_KEYBOARDBUTTON));
    _AddInput("p", Input(33, INPUT_KEYBOARDBUTTON));
    _AddInput("q", Input(24, INPUT_KEYBOARDBUTTON));
    _AddInput("r", Input(27, INPUT_KEYBOARDBUTTON));
    _AddInput("s", Input(39, INPUT_KEYBOARDBUTTON));
    _AddInput("t", Input(28, INPUT_KEYBOARDBUTTON));
    _AddInput("u", Input(30, INPUT_KEYBOARDBUTTON));
    _AddInput("v", Input(55, INPUT_KEYBOARDBUTTON));
    _AddInput("w", Input(25, INPUT_KEYBOARDBUTTON));
    _AddInput("x", Input(53, INPUT_KEYBOARDBUTTON));
    _AddInput("y", Input(29, INPUT_KEYBOARDBUTTON));
    _AddInput("z", Input(52, INPUT_KEYBOARDBUTTON));

    _AddInput("f1", Input(67, INPUT_KEYBOARDBUTTON));
    _AddInput("f2", Input(68, INPUT_KEYBOARDBUTTON));
    _AddInput("f3", Input(69, INPUT_KEYBOARDBUTTON));
    _AddInput("f4", Input(70, INPUT_KEYBOARDBUTTON));
    _AddInput("f5", Input(71, INPUT_KEYBOARDBUTTON));
    _AddInput("f6", Input(72, INPUT_KEYBOARDBUTTON));
    _AddInput("f7", Input(73, INPUT_KEYBOARDBUTTON));
    _AddInput("f8", Input(74, INPUT_KEYBOARDBUTTON));
    _AddInput("f9", Input(75, INPUT_KEYBOARDBUTTON));
    _AddInput("f10", Input(76, INPUT_KEYBOARDBUTTON));
    _AddInput("f11", Input(95, INPUT_KEYBOARDBUTTON));
    _AddInput("f12", Input(96, INPUT_KEYBOARDBUTTON));

    _AddInput("escape", Input(9, INPUT_KEYBOARDBUTTON));
    _AddInput("tab", Input(23, INPUT_KEYBOARDBUTTON));
    _AddInput("shift", Input(50, INPUT_KEYBOARDBUTTON));
    _AddInput("enter", Input(36, INPUT_KEYBOARDBUTTON));
    _AddInput("space", Input(65, INPUT_KEYBOARDBUTTON));
    _AddInput("backspace", Input(22, INPUT_KEYBOARDBUTTON));
    _AddInput("control", Input(37, INPUT_KEYBOARDBUTTON));
    _AddInput("alt", Input(64, INPUT_KEYBOARDBUTTON));

    //Mouse
    _AddInput("leftclick", Input(kCGMouseButtonLeft, INPUT_MOUSEBUTTON));
    _AddInput("middleclick", Input(kCGMouseButtonCenter, INPUT_MOUSEBUTTON));
    _AddInput("rightclick", Input(kCGMouseButtonRight, INPUT_MOUSEBUTTON));
    _AddInput("scrollup", Input(4, INPUT_MOUSEWHEEL));
    _AddInput("scrolldown", Input(5, INPUT_MOUSEWHEEL));
    */
}

std::string MacPlatform::GetOSName()const
{
    //TODO: provide more useful information
    return "Mac";
}

void MacPlatform::_OSFakeKeyPress(int keycode, bool pressed)
{
    CGEventRef event = CGEventCreateKeyboardEvent (NULL, keycode, pressed);
    CFRelease(event);
}

void MacPlatform::_OSFakeMouseMove(int x, int y)
{

}

void MacPlatform::_OSFakeMouseButton(int button, bool pressed)
{
    CGEventRef event

    if(pressed)
        event = CGEventCreateMouseEvent(NULL, kCGEventOtherMouseDown, CGPoint mouseCursorPosition, button);

    else
        event = CGEventCreateMouseEvent(NULL, kCGEventOtherMouseUp, CGPoint mouseCursorPosition, button);

    CFRelease(event);
}

void MacPlatform::_OSFakeMouseWheel(int direction, bool pressed)
{

}

MacPlatform::~MacPlatform()
{
    ClearEvents();
}

#endif
