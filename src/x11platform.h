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
	virtual void _OSFakeKeyPress(int keycode, bool pressed)override;
	virtual void _OSFakeMouseMove(int x, int y)override;
	virtual void _OSFakeMouseButton(int button, bool pressed)override;
	virtual void _OSFakeMouseWheel(int direction, bool pressed)override;

	Display *_display;
	void _Flush();
};

#endif
