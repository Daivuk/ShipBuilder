#pragma once
#include "onut.h"

enum class eGlobalState
{
    INITIAL_LOADING,
    MAIN_MENU,
    SHIP_BUILDER
};

class BaseState
{
public:
    virtual void init() {}
    virtual void update() {}
    virtual void render() {}
};

class GlobalStateManager : public onut::State < eGlobalState >, public BaseState
{
public:
    GlobalStateManager();

    void init() override;
    void update() override;
    void render() override;

protected:
    bool onLeaveState(eGlobalState oldState, eGlobalState newState) override;
    void onEnterState(eGlobalState newState) override;
};
