#include "MainMenuState.h"

MainMenuState::MainMenuState() :
    onut::State<eMainMenuState>(eMainMenuState::IDLE)
{
}

void MainMenuState::init()
{
}

void MainMenuState::update()
{
}

void MainMenuState::render()
{
}

bool MainMenuState::onLeaveState(eMainMenuState oldState, eMainMenuState newState)
{
    return true;
}

void MainMenuState::onEnterState(eMainMenuState newState)
{
}
