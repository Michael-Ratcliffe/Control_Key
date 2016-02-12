#ifdef __linux__
#include "x11platform.h"

//Qt will not compile unless the includes are in source file
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>


X11Platform::X11Platform()
{
	_display = XOpenDisplay(0);
	//Keyboard
	_AddInput("a", Input(XK_a, INPUT_KEYBOARDBUTTON));
	_AddInput("b", Input(XK_b, INPUT_KEYBOARDBUTTON));
	_AddInput("c", Input(XK_c, INPUT_KEYBOARDBUTTON));
	_AddInput("d", Input(XK_d, INPUT_KEYBOARDBUTTON));
	_AddInput("e", Input(XK_e, INPUT_KEYBOARDBUTTON));
	_AddInput("f", Input(XK_f, INPUT_KEYBOARDBUTTON));
	_AddInput("g", Input(XK_g, INPUT_KEYBOARDBUTTON));
	_AddInput("h", Input(XK_h, INPUT_KEYBOARDBUTTON));
	_AddInput("i", Input(XK_i, INPUT_KEYBOARDBUTTON));
	_AddInput("j", Input(XK_j, INPUT_KEYBOARDBUTTON));
	_AddInput("k", Input(XK_k, INPUT_KEYBOARDBUTTON));
	_AddInput("l", Input(XK_l, INPUT_KEYBOARDBUTTON));
	_AddInput("m", Input(XK_m, INPUT_KEYBOARDBUTTON));
	_AddInput("n", Input(XK_n, INPUT_KEYBOARDBUTTON));
	_AddInput("o", Input(XK_o, INPUT_KEYBOARDBUTTON));
	_AddInput("p", Input(XK_p, INPUT_KEYBOARDBUTTON));
	_AddInput("q", Input(XK_q, INPUT_KEYBOARDBUTTON));
	_AddInput("r", Input(XK_r, INPUT_KEYBOARDBUTTON));
	_AddInput("s", Input(XK_s, INPUT_KEYBOARDBUTTON));
	_AddInput("t", Input(XK_t, INPUT_KEYBOARDBUTTON));
	_AddInput("u", Input(XK_u, INPUT_KEYBOARDBUTTON));
	_AddInput("v", Input(XK_v, INPUT_KEYBOARDBUTTON));
	_AddInput("w", Input(XK_w, INPUT_KEYBOARDBUTTON));
	_AddInput("x", Input(XK_x, INPUT_KEYBOARDBUTTON));
	_AddInput("y", Input(XK_y, INPUT_KEYBOARDBUTTON));
	_AddInput("z", Input(XK_z, INPUT_KEYBOARDBUTTON));

	_AddInput("f1", Input(XK_F1, INPUT_KEYBOARDBUTTON));
	_AddInput("f2", Input(XK_F2, INPUT_KEYBOARDBUTTON));
	_AddInput("f3", Input(XK_F3, INPUT_KEYBOARDBUTTON));
	_AddInput("f4", Input(XK_F4, INPUT_KEYBOARDBUTTON));
	_AddInput("f5", Input(XK_F5, INPUT_KEYBOARDBUTTON));
	_AddInput("f6", Input(XK_F6, INPUT_KEYBOARDBUTTON));
	_AddInput("f7", Input(XK_F7, INPUT_KEYBOARDBUTTON));
	_AddInput("f8", Input(XK_F8, INPUT_KEYBOARDBUTTON));
	_AddInput("f9", Input(XK_F9, INPUT_KEYBOARDBUTTON));
	_AddInput("f10", Input(XK_F10, INPUT_KEYBOARDBUTTON));
	_AddInput("f11", Input(XK_F11, INPUT_KEYBOARDBUTTON));
	_AddInput("f12", Input(XK_F12, INPUT_KEYBOARDBUTTON));

	_AddInput("escape", Input(XK_Escape, INPUT_KEYBOARDBUTTON));
	_AddInput("tab", Input(XK_Tab, INPUT_KEYBOARDBUTTON));
	_AddInput("shift", Input(XK_Shift_L, INPUT_KEYBOARDBUTTON));
	_AddInput("enter", Input(XK_Return, INPUT_KEYBOARDBUTTON));
	_AddInput("space", Input(XK_space, INPUT_KEYBOARDBUTTON));
	_AddInput("backspace", Input(XK_BackSpace, INPUT_KEYBOARDBUTTON));
	_AddInput("control", Input(XK_Control_L, INPUT_KEYBOARDBUTTON));
	_AddInput("alt", Input(XK_Alt_L, INPUT_KEYBOARDBUTTON));

	//Mouse
	_AddInput("leftclick", Input(1, INPUT_MOUSEBUTTON));
	_AddInput("middleclick", Input(2, INPUT_MOUSEBUTTON));
	_AddInput("rightclick", Input(3, INPUT_MOUSEBUTTON));
	_AddInput("scrollup", Input(4, INPUT_MOUSEWHEEL));
	_AddInput("scrolldown", Input(5, INPUT_MOUSEWHEEL));
}

std::string X11Platform::GetOSName()const
{
    //TODO: provide more useful information
    return "Linux";
}

void X11Platform::_OSFakeKeyPress(int keycode, bool pressed)
{
	keycode = (int)XKeysymToKeycode(_display, keycode);
	XTestFakeKeyEvent(_display, keycode, pressed, 0);
	_Flush();
}

void X11Platform::_OSFakeMouseMove(int x, int y)
{
	XTestFakeRelativeMotionEvent(_display, x, y, 0);
	_Flush();
}

void X11Platform::_OSFakeMouseButton(int button, bool pressed)
{
	XTestFakeButtonEvent(_display, button, pressed, 0);
	_Flush();
}

void X11Platform::_OSFakeMouseWheel(int direction, bool pressed)
{
    if(pressed && doubleScroll)
	{
        //The code below will simulate a few scroll clicks
		//This is required for some games
		XTestFakeButtonEvent(_display, direction, true, 0);
		_Flush();
		XTestFakeButtonEvent(_display, direction, false, 0);
		_Flush();
		XTestFakeButtonEvent(_display, direction, true, 0);
	}

	else
		XTestFakeButtonEvent(_display, direction, pressed, 0);

	_Flush();
}

void X11Platform::_Flush()
{
	XFlush(_display);

	//uneeded?
	XTestDiscard(_display);
}

X11Platform::~X11Platform()
{
	ClearEvents();
	XCloseDisplay(_display);
}

#endif
