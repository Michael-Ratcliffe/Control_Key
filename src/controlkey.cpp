#include "controlkey.h"

ControlKey::ControlKey()
{

}

bool ControlKey::Init(std::string controllerDB)
{
    std::cout << "OS: " << platform.GetOSName() << std::endl;

    if(SDL_Init(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) > 0)
    {
        std::cout << "SDL_Init() Failed" << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GameControllerEventState(SDL_ENABLE);

    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);

    std::cout << "SDL Version: " << (int)linked.major << "." << (int)linked.minor << "." << (int)linked.patch
    << " Loaded" << std::endl;

    std::cout << "Compiled Against SDL Version: " << (int)compiled.major << "." << (int)compiled.minor << "." << (int)compiled.patch
    << std::endl;

    int ret = SDL_GameControllerAddMappingsFromFile(controllerDB.c_str());

    if(ret == -1)
    {
        std::cout << "Failed To Load Controller Database " << controllerDB << " " << SDL_GetError() << std::endl;
        std::cout << "Without A Controller Database Some Controllers May Not Work: " << std::endl;
    }
    else
        std::cout << ret << " Controller Mappings Loaded From: " << controllerDB << std::endl;

    return true;
}

void ControlKey::LoadConfig(std::string filePath)
{
    ConfigParser config(filePath);
        platform.SetConfig(&config);
        controller.SetConfig(&config);
    config.Close();
}

void ControlKey::ClearConfig()
{
    //Sending a non existing file clears config;
    ConfigParser config("");
        platform.SetConfig(&config);
        controller.SetConfig(&config);
    config.Close();

    platform.ClearEvents();
    std::cout << "Cleared Config" << std::endl;
}

void ControlKey::Update()
{
    controller.Update(&platform);
}

void ControlKey::Execute()
{
	while(!controller.Quit())
	{
		if(!controller.IsOpen())
			controller.OpenFirstAvailable();

        Update();
		SDL_Delay(8);
	}
}

ControlKey::~ControlKey()
{
    controller.Close();
    SDL_Quit();
}
