#pragma once
#include "CircuitFx.h"

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
    OAnimc      m_fadeAnim = Color::Black;
    OAnimf      m_strokeAnim = 0.f;
    OAnimf      m_smallStrokeAnim = 0.f;
    OAnimf      m_btnAnim[3];
    OAnimc      m_btnShadows[3];
    OAnimStr    m_btnText[3];
    OAnimf      m_btnSelection[3];
    CircuitFx   m_circuitFx;
    int         m_selection = -1;
};
