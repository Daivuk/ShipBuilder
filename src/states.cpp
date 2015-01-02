#include "states.h"
#include "InitialLoadingState.h"
#include "MainMenuState.h"

onut::StateManager<eGlobalState> g_stateManager(eGlobalState::INITIAL_LOADING,
{
    onut::DefineState<InitialLoadingState>(eGlobalState::INITIAL_LOADING),
    onut::DefineState<MainMenuState>(eGlobalState::MAIN_MENU)
});
