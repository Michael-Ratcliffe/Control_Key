#include <windows.h>
#include "platform.h"

class WindowsPlatform: public Platform
{
public:
	WindowsPlatform();
	virtual ~WindowsPlatform();

    virtual std::string GetOSName()const override;

private:
	virtual void _OSFakeKeyPress(int keycode, bool pressed)override;
	virtual void _OSFakeMouseMove(int x, int y)override;
	virtual void _OSFakeMouseButton(int button, bool pressed)override;
	virtual void _OSFakeMouseWheel(int direction, bool pressed)override;
};
