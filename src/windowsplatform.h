#include <windows.h>
#include "platform.h"

class WindowsPlatform: public Platform
{
public:
	WindowsPlatform();
	virtual ~WindowsPlatform();

    virtual std::string GetOSName()const override;

private:
	virtual void _FakeKeyPress(int keycode, bool pressed)override;
	virtual void _FakeMouseMove(int x, int y)override;
	virtual void _FakeMouseButton(int button, bool pressed)override;
	virtual void _FakeMouseWheel(int wheel, bool pressed)override;
};
