#include <windows.h>
#include "platform.h"

class WindowsPlatform: public Platform
{
public:
	WindowsPlatform();
	virtual ~WindowsPlatform();

    virtual std::string GetOSName()const override;
	virtual void SimulateKey(int keycode, bool pressed)override;
	virtual void SimulateMouseMove(int x, int y)override;
	virtual void SimulateMouseButton(int button, bool pressed)override;
	virtual void SimulateMouseWheel(int wheel, bool pressed)override;
};
