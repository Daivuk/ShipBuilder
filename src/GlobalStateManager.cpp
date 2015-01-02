#include "GlobalStateManager.h"

GlobalStateManager::GlobalStateManager() :
    onut::State<eGlobalState>(eGlobalState::INITIAL_LOADING)
{
}

bool GlobalStateManager::onLeaveState(eGlobalState oldState, eGlobalState newState)
{
    return true;
}

void GlobalStateManager::onEnterState(eGlobalState newState)
{
}

void GlobalStateManager::init()
{
}

void GlobalStateManager::update()
{
}

void GlobalStateManager::render()
{
}
