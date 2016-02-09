#ifndef X11PLATFORM_H
#define X11PLATFORM_H
#include "platform.h"

typedef struct _XDisplay Display;

class X11Platform: public Platform
{
public:
	X11Platform();
	virtual ~X11Platform();

    virtual std::string GetOSName()const override;

private:
	virtual void _FakeKeyPress(int keycode, bool pressed)override;
	virtual void _FakeMouseMove(int x, int y)override;
	virtual void _FakeMouseButton(int button, bool pressed)override;
	virtual void _FakeMouseWheel(int wheel, bool pressed)override;

	Display *_display;
	void _Flush();
};

#endif
