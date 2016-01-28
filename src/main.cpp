#include <iostream>
#include "controlkey.h"

ControlKey controlKey;

#undef main

int main(int argc, char *argv[])
{
    if(argc == 2)
        controlKey.LoadConfig(argv[1]);
    else if(argc > 2)
    {
        std::cout << "Error! To Many Arguments!" << std::endl;
        return -1;
    }
    else
        controlKey.LoadConfig("config/default.conf");

    if(!controlKey.Init("config/gamecontrollerdb.txt"))
    {
        std::cout << "Failed To Initialize!" << std::endl;
        return -1;
    }

    controlKey.Execute();
}
