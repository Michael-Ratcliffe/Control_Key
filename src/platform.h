#ifndef PLATFORM_H
#define PLATFORM_H
#include <iostream>
#include <map>
#include <vector>
#include "configparser.h"
#include "vector2f.h"

enum InputType
{
    INPUT_UNKNOWN,
    INPUT_KEYBOARDBUTTON,
    INPUT_MOUSEBUTTON,
    INPUT_MOUSEWHEEL
};

struct Input
{
    Input(): code(0), type(INPUT_UNKNOWN){}

    Input(int code, InputType type): code(code), type(type)
    {

    }

    Input &operator =(const Input &rhs)
    {
        this->code = rhs.code;
        this->type = rhs.type;
        return *this;
    }

    int code;
    InputType type;
};

class Platform
{
public:
    Platform();
	virtual ~Platform();

    void SetConfig(ConfigParser *config);
    void SimulateMouse(Vector2f pos);
    void SimulateButton(std::string inputString, bool simulate);
    void ClearEvents();
    std::vector<std::string> GetInputList()const;
    virtual std::string GetOSName()const=0;

    float mouseSensitivity;
    bool doubleScroll;

protected:
    void _AddInput(std::string, Input input);
    Input _GetInputFromStr(std::string inputString)const;

private:
    virtual void _FakeKeyPress(int keycode, bool pressed)=0;
    virtual void _FakeMouseMove(int x, int y)=0;
    virtual void _FakeMouseButton(int button, bool pressed)=0;
    virtual void _FakeMouseWheel(int wheel, bool pressed)=0;

    std::map<std::string, Input> _inputMap;
    std::map<std::string, bool> _previousState;
    std::string _validInputs;
    float _previousTime;
};

#endif
