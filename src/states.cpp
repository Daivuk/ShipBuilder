#include "states.h"
#include "InitialLoadingState.h"
#include "MainMenuState.h"
#include "PlayState.h"

onut::StateManager<eGlobalState> g_stateManager(eGlobalState::INITIAL_LOADING,
{
    onut::DefineState<InitialLoadingState>(eGlobalState::INITIAL_LOADING),
    onut::DefineState<MainMenuState>(eGlobalState::MAIN_MENU),
    onut::DefineState<PlayState>(eGlobalState::PLAY),
});
