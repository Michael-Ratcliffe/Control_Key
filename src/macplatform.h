#ifndef MACPLATFORM_H
#define MACPLATFORM_H
#include "platform.h"

class MacPlatform: public Platform
{
public:
	MacPlatform();
	virtual ~MacPlatform();

	virtual std::string GetOSName()const override;
	virtual void SimulateKey(int keycode, bool pressed)override;
	virtual void SimulateMouseMove(int x, int y)override;
	virtual void SimulateMouseButton(int button, bool pressed)override;
	virtual void SimulateMouseWheel(int wheel, bool pressed)override;
};

#endif
