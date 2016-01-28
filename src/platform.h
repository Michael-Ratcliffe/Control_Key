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
    void UpdateMouseMovement(Vector2f pos);
    void SimulateEvent(std::string inputString, float val);
    void ClearEvents();
    std::vector<std::string> GetInputList()const;

    virtual std::string GetOSName()const=0;
	virtual void SimulateKey(int keycode, bool pressed)=0;
	virtual void SimulateMouseMove(int x, int y)=0;
    virtual void SimulateMouseButton(int button, bool pressed)=0;
    virtual void SimulateMouseWheel(int wheel, bool pressed)=0;

    float mouseSensitivity;
    bool doubleScroll;

protected:
    void _AddInput(std::string, Input input);
    Input _GetInputFromStr(std::string inputString)const;

private:
    std::map<std::string, Input> _inputMap;
    std::map<std::string, bool> _previousState;
    std::string _validInputs;
    float _previousTime;
};

#endif
