#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <SDL2/SDL.h>
#include <map>
#include <iostream>
#include "configparser.h"
#include "platform.h"
#include "vector2f.h"

enum Analog
{
    ANALOG_LEFT,
    ANALOG_RIGHT
};

enum Trigger
{
    TRIGGER_LEFT,
    TRIGGER_RIGHT
};

class Controller
{
public:
    Controller();
    ~Controller();

    static int GetNumControllers();
    static std::vector<std::string> GetContollerNames();

    bool OpenFirstAvailable();
    bool Open(int index);
    bool IsOpen()const;
    void Close();
    void SetConfig(ConfigParser *config);
    void Update(Platform *platform);
    float GetAxis(SDL_GameControllerAxis axis)const;
    Vector2f GetAnalogAxis(Analog analog)const;
    float GetTriggerAxis(Trigger trigger)const;
    std::string GetMapping(std::string name)const;
    std::map<std::string, std::string> GetInputMappings()const;
    bool Quit();

    Analog mouseLookAnalog;
    bool sendEvents;
    //Deadzones
    float leftAxisDZ;
    float rightAxisDZ;
    float triggerDZ;

private:
    void _PollAxisState();
    void _PollButtonState();
    int _indexID;
    //Used to bring SDL2 axis values -32768 to 32767; to -1.0 to 1.0
    //Except for triggers, they never go negative.
    const int _axisNormalizer = 32767;

    SDL_GameController *_SDLController;
    std::map<std::string, std::string> _mappings;
    //_curentState is a map of all axes and buttons with a float value
    //representing their current state.
    std::map<std::string, float> _currentState;
};

#endif
