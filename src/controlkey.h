#ifndef CONTROLKEY_H
#define CONTROLKEY_H
#include <iostream>
#include <SDL2/SDL.h>
#include "controller.h"
#include "configparser.h"

#ifdef __linux__
    #include "x11platform.h"
#endif

#ifdef _WIN32
    #include "windowsplatform.h"
#endif

#ifdef __MACH__
    #include "macplatform.h"
#endif

class ControlKey
{
public:
    ControlKey();
    ~ControlKey();

    Controller controller;

    #ifdef __linux__
        X11Platform platform;
    #endif

    #ifdef _WIN32
        WindowsPlatform platform;
    #endif

    #ifdef __MACH__
        MacPlatform platform;
    #endif

    bool Init(std::string controllerDB);
    void LoadConfig(std::string filePath);
    void ClearConfig();
    void Update();
    void Execute();
};

#endif
