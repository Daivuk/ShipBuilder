#include <Windows.h>
#include "states.h"

OPal g_pal = {
    OColorHex(FFC675),
    OColorHex(F2A324),
    OColorHex(F6433E),
    OColorHex(9E023B),
    OColorHex(14133B),
    OColorHex(14133B).AdjustedSaturation(2.f),
    OColorHex(14133B).AdjustedSaturation(4.f),
    OColorHex(14133B),
    OColorHex(14133B),
};

int CALLBACK WinMain(HINSTANCE appInstance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdCount)
{
    {
        auto color = Color::Lerp(Color::White, g_pal[4], .5f);
        color.AdjustContrast(2.f);
        g_pal[7] = color;
        color.AdjustContrast(2.f);
        g_pal[8] = color;
    }

    OSettings->setResolution({1280, 720});
    OSettings->setGameName("Ship Builder");

    onut::run(g_stateManager);

    return 0;
}
