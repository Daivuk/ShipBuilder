#pragma once
#include "onut.h"

enum class eGlobalState
{
    INITIAL_LOADING,
    MAIN_MENU,
    SHIP_BUILDER
};

extern onut::StateManager<eGlobalState> g_stateManager;
