#ifndef MACPLATFORM_H
#define MACPLATFORM_H
#include "platform.h"

//All code here is preliminary and does NOT work yet.

class MacPlatform: public Platform
{
public:
	MacPlatform();
	virtual ~MacPlatform();

	virtual std::string GetOSName()const override;

private:
	virtual void _OSFakeKeyPress(int keycode, bool pressed)override;
	virtual void _OSFakeMouseMove(int x, int y)override;
	virtual void _OSFakeMouseButton(int button, bool pressed)override;
	virtual void _OSFakeMouseWheel(int direction, bool pressed)override;
};

#endif
