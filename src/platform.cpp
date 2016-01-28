#include "platform.h"
#include <SDL2/SDL.h>
#include <cmath>

Platform::Platform()
{
    _previousTime = 0.f;
    _validInputs = "a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,"
    "1,2,3,4,5,6,7,8,9,0,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,escape,"
    "tab,shift,enter,space,backspace,control,alt,leftclick,"
    "middleclick,rightclick,scrollup,scrolldown";
}

void Platform::SetConfig(ConfigParser *config)
{
    //Clear current config
    mouseSensitivity = 1.f;
    doubleScroll = false;

    config->FillValue(mouseSensitivity, "mousesensitivity", "[Config]");
    config->FillValue(doubleScroll, "doublescroll", "[Config]");
}

void Platform::UpdateMouseMovement(Vector2f pos)
{
    float current = SDL_GetTicks();
    float deltaTime = current - _previousTime;

    float x = (mouseSensitivity * pos.x) * deltaTime;
    float y = (mouseSensitivity * pos.y) * deltaTime;

    SimulateMouseMove(x, y);
    _previousTime = current;
}

void Platform::SimulateEvent(std::string inputString, float val)
{
    //inputString is the mapped key/mouse button to a controller input
    //val is ether 0 or 1 for a button. Or the axis value if its an axis
    Input input = _GetInputFromStr(inputString);

    //If the input state is the same as the last time.
    //Without this the user cannot use mapped keys/buttons while the application runs.
    //Also corrects input issues on windows.
    if(_previousState[inputString] == (bool)val)
        return;

///*debug
    if(inputString != "none")
        std::cout << inputString << " " << val << std::endl;
//*/
    switch(input.type)
    {
        case INPUT_KEYBOARDBUTTON:
            if(val == 0)
                SimulateKey(input.code, false);
            else
                SimulateKey(input.code, true);
        break;

        case INPUT_MOUSEBUTTON:
            if(val == 0)
                SimulateMouseButton(input.code, false);
            else
                SimulateMouseButton(input.code, true);
        break;

        case INPUT_MOUSEWHEEL:
            if(val == 0)
                SimulateMouseWheel(input.code, false);
            else
                SimulateMouseWheel(input.code, true);
        break;

        case INPUT_UNKNOWN:

        break;
    }

    _previousState[inputString] = val;
}

void Platform::ClearEvents()
{
    for(auto &i : _inputMap)
    {
        SimulateEvent(i.first, 0);
    }

    _previousState.clear();
    std::cout << "Cleared All Platform Events" << std::endl;
}

std::vector<std::string> Platform::GetInputList()const
{
    std::vector<std::string> vec;
    for(auto &i: _inputMap)
    {
        vec.push_back(i.first);
    }
    return vec;
}

void Platform::_AddInput(std::string inputString, Input input)
{
    //This makes sure that there are no typos in the platform _inputMap.
    //All platforms, x11, windows, mac etc must have the same names for inputs
    std::size_t found = _validInputs.find(inputString);
    if(found != std::string::npos)
        _inputMap[inputString] = input;

    else
    {
        std::cout << "Input: <"  << inputString << "> Is Not A Valid Platform Input" << std::endl;
        throw std::exception();
    }
}

Input Platform::_GetInputFromStr(std::string inputString)const
{
    auto i = _inputMap.find(inputString);
    if(i != _inputMap.end())
    {
        return (*i).second;
    }
    //Unknown Input
    return Input();
}

Platform::~Platform()
{

}
