#pragma once
#include "Button.h"
#include "CircuitFx.h"

enum class eMainMenuState
{
    IDLE,
    FADE_OUT
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
    void startFadeOut(int buttonId);

    OAnimc      m_fadeAnim = Color::Black;
    OAnimf      m_strokeAnim = 0.f;
    OAnimf      m_smallStrokeAnim = 0.f;
    CircuitFx   m_circuitFx;
    Button      m_buttons[5];
    int         m_selection = 4;
};
