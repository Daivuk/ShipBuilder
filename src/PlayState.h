#pragma once
#include "onut.h"
#include "Ship.h"

enum class ePlayState
{
    HYPER_SPACE_COMING_IN,
    COMBAT,
};

class PlayState : public onut::State < ePlayState >
{
public:
    PlayState();
    virtual ~PlayState();

    void init() override;
    void update() override;
    void render() override;

protected:
    bool onLeaveState(ePlayState oldState, ePlayState newState) override;
    void onEnterState(ePlayState newState) override;

private:
    Ship*   m_pMyShip = nullptr;
    Ship*   m_pEnemyShip = nullptr;
};
