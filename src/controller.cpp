#include "controller.h"
#include <cmath>

Controller::Controller()
{
    _SDLController = nullptr;
    sendEvents = true;
    _indexID = -1;
}

int Controller::GetNumControllers()
{
    return SDL_NumJoysticks();
}

std::vector<std::string> Controller::GetContollerNames()
{
    std::vector<std::string> vec;

    for(int i = 0; i < GetNumControllers(); i++)
    {
        if(SDL_IsGameController(i))
            vec.push_back(std::string(SDL_GameControllerNameForIndex(i)) + " " + std::to_string(i));
        else
            vec.push_back("Not Supported: " + std::string(SDL_JoystickNameForIndex(i)) + " " + std::to_string(i));
    }
    return vec;
}

bool Controller::OpenFirstAvailable()
{
    for(int i = 0; i < GetNumControllers(); i++)
    {
        if(Open(i))
        {
            return true;
        }
    }
    return false;
}

bool Controller::Open(int index)
{
    //Only open controller if its a game controller and its not already open
    if(SDL_IsGameController(index) && _indexID != index)
    {
        Close();
        _SDLController = SDL_GameControllerOpen(index);
        if(_SDLController)
        {
            _indexID = index;
            std::cout << "Opened Controller <" << SDL_GameControllerName(_SDLController)
            << "> With Index: " << _indexID << std::endl;
            return true;
        }
        else
            std::cout << "Failed To Open Controller " << SDL_GetError() << std::endl;
    }
    return false;
}

bool Controller::IsOpen()const
{
    if(_SDLController)
        return true;
    else
        return false;
}

void Controller::Close()
{
    if(IsOpen())
    {
        std::cout << "Closing Controller <" << SDL_GameControllerName(_SDLController) << "> With Index: " << _indexID << std::endl;
        SDL_GameControllerClose(_SDLController);
        _SDLController = nullptr;
        _indexID = -1;
    }
}

void Controller::SetConfig(ConfigParser *config)
{
    //Clear Current Config First
    _mappings.clear();
    _currentState.clear();
    mouseLookAnalog = ANALOG_RIGHT;
    leftAxisDZ = 0.25f;
    rightAxisDZ = 0.25f;
    triggerDZ = 0.1f;

    config->FillValue((int&)mouseLookAnalog, "mouselookanalog", "[Config]");
    config->FillValue(leftAxisDZ, "leftaxisdz", "[Config]");
    config->FillValue(rightAxisDZ, "rightaxisdz", "[Config]");
    config->FillValue(triggerDZ, "triggerdz", "[Config]");
    config->FillMap(_mappings, "[Mappings]");
}

void Controller::Update(Platform *platform)
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_CONTROLLERDEVICEREMOVED:
                std::cout << "Controller: " << e.cdevice.which << " Removed" << std::endl;

                if(e.cdevice.which == _indexID)
                {
                    Close();
                }
            break;
        }
    }

    if(!IsOpen() || !sendEvents)
        return;

    _PollAxisState();
    _PollButtonState();

    for(auto &i : _currentState)
    {
        std::string str = GetMapping(i.first);
        platform->SimulateEvent(str, i.second);
    }

    platform->UpdateMouseMovement(GetAnalogAxis(mouseLookAnalog));
}

float Controller::GetAxis(SDL_GameControllerAxis axis)const
{
    switch(axis)
    {
        case SDL_CONTROLLER_AXIS_LEFTX:
            return GetAnalogAxis(ANALOG_LEFT).x;
        break;

        case SDL_CONTROLLER_AXIS_LEFTY:
            return GetAnalogAxis(ANALOG_LEFT).y;
        break;

        case SDL_CONTROLLER_AXIS_RIGHTX:
            return GetAnalogAxis(ANALOG_RIGHT).x;
        break;

        case SDL_CONTROLLER_AXIS_RIGHTY:
            return GetAnalogAxis(ANALOG_RIGHT).y;
        break;

        case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
            return GetTriggerAxis(TRIGGER_LEFT);
        break;

        case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
            return GetTriggerAxis(TRIGGER_RIGHT);
        break;

        default:
            return 0.f;
        break;
    }
}

Vector2f Controller::GetAnalogAxis(Analog analog)const
{
    float dz = 0.f;
    bool isRadial = false;
    Vector2f vec;

    if(analog == ANALOG_LEFT)
    {
        dz = leftAxisDZ;

        if(mouseLookAnalog == ANALOG_LEFT)
            isRadial = true;

        vec.x = SDL_GameControllerGetAxis(_SDLController, SDL_CONTROLLER_AXIS_LEFTX);
        vec.y = SDL_GameControllerGetAxis(_SDLController, SDL_CONTROLLER_AXIS_LEFTY);
    }
    else if(analog == ANALOG_RIGHT)
    {
        dz = rightAxisDZ;

        if(mouseLookAnalog == ANALOG_RIGHT)
            isRadial = true;

        vec.x = SDL_GameControllerGetAxis(_SDLController, SDL_CONTROLLER_AXIS_RIGHTX);
        vec.y = SDL_GameControllerGetAxis(_SDLController, SDL_CONTROLLER_AXIS_RIGHTY);
    }
    else
        return Vector2f::Zero;

    vec /= _axisNormalizer;

    if(isRadial)
    {
        if(vec.Magnitude() < dz)
            vec = Vector2f::Zero;
        else
            vec = vec.Normalized() * ((vec.Magnitude() - dz) / (1 - dz));
    }

    else
    {
        if(std::fabs(vec.x) < dz)
            vec.x = 0.f;
        if(std::fabs(vec.y) < dz)
            vec.y = 0.f;
    }

    return vec;
}

float Controller::GetTriggerAxis(Trigger trigger)const
{
    float val;

    if(trigger == TRIGGER_LEFT)
        val = SDL_GameControllerGetAxis(_SDLController, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
    else if(trigger == TRIGGER_RIGHT)
        val = SDL_GameControllerGetAxis(_SDLController, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
    else
        return 0.f;

    val /= _axisNormalizer;

    if(val < triggerDZ)
        val = 0.f;

    return val;
}

void Controller::_PollAxisState()
{
    /*SDL provides string names for each axis.
    This function retrieves the names of all axes and adds a "+" or "-"
    on the end of the string depending on its state.
    This makes it possible for a positive axis position to do something different than its negative position;
    */
    for(int i = 0; i < SDL_CONTROLLER_AXIS_MAX; i++)
    {
        std::string name = SDL_GameControllerGetStringForAxis((SDL_GameControllerAxis)i);
        float val = GetAxis((SDL_GameControllerAxis)i);

        if(i == SDL_CONTROLLER_AXIS_TRIGGERRIGHT || i == SDL_CONTROLLER_AXIS_TRIGGERLEFT)
        {
            //Triggers do not get appended with "-" or "+" they contain only positive values
            _currentState[name] = val;
        }

        else
        {
            if(val > 0.f)
                _currentState[name+"+"] = val;
            else if(val < 0.f)
                _currentState[name+"-"] = val;
            else //val == 0.f
            {
                _currentState[name+"+"] = val;//0
                _currentState[name+"-"] = val;//0
            }
        }
    }
}

void Controller::_PollButtonState()
{
    /*SDL provides string names for each button.
    This function retrieves the names of all the buttons and maps them to a state.
    The state values are 0 for unpressed and 1 for currently pressed.
    */
    for(int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++)
    {
        std::string name = SDL_GameControllerGetStringForButton((SDL_GameControllerButton)i);
        int val = SDL_GameControllerGetButton(_SDLController, (SDL_GameControllerButton)i);
        _currentState[name] = val;
    }
}

std::string Controller::GetMapping(std::string name)const
{
    auto i = _mappings.find(name);
    if(i != _mappings.end())
    {
        return (*i).second;
    }
    return "none";
}

std::map<std::string, std::string> Controller::GetInputMappings()const
{
    return _mappings;
}

bool Controller::Quit()
{
    return(SDL_GameControllerGetButton(_SDLController, SDL_CONTROLLER_BUTTON_START)
    && SDL_GameControllerGetButton(_SDLController, SDL_CONTROLLER_BUTTON_BACK)
    && SDL_GameControllerGetButton(_SDLController, SDL_CONTROLLER_BUTTON_LEFTSHOULDER)
    && SDL_GameControllerGetButton(_SDLController, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER));
}

Controller::~Controller()
{
}
