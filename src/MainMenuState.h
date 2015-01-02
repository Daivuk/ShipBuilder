#pragma once
#include "onut.h"

enum class eMainMenuState
{
    IDLE
};

class MainMenuState : public onut::State < eMainMenuState >
{
public:
    MainMenuState();

    void init() override;
    void update() override;
    void render() override;

protected:
    virtual bool onLeaveState(eMainMenuState oldState, eMainMenuState newState) override;
    virtual void onEnterState(eMainMenuState newState) override;

private:
};
