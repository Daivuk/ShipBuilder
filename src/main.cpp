#include <Windows.h>
#include "onut.h"

int CALLBACK WinMain(HINSTANCE appInstance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdCount)
{
    onut::run(nullptr, nullptr, nullptr);

    return 0;
}
