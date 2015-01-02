#include <Windows.h>
#include "states.h"

int CALLBACK WinMain(HINSTANCE appInstance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdCount)
{
    OSettings->setResolution({1280, 720});
    OSettings->setGameName("Ship Builder");

    onut::run(g_stateManager);

    return 0;
}
