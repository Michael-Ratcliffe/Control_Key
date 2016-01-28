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
	virtual void SimulateKey(int keycode, bool pressed)override;
	virtual void SimulateMouseMove(int x, int y)override;
	virtual void SimulateMouseButton(int button, bool pressed)override;
	virtual void SimulateMouseWheel(int wheel, bool pressed)override;

private:
	Display *_display;
	void _Flush();
};

#endif
