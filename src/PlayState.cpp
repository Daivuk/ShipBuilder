#include "PlayState.h"

PlayState::PlayState() :
    onut::State<ePlayState>(ePlayState::HYPER_SPACE_COMING_IN)
{
}

PlayState::~PlayState()
{
}

void PlayState::init()
{
}

void PlayState::update()
{
}

void PlayState::render()
{
}

bool PlayState::onLeaveState(ePlayState oldState, ePlayState newState)
{
    return true;
}

void PlayState::onEnterState(ePlayState newState)
{
}
