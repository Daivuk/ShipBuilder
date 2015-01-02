#include "MainMenuState.h"

MainMenuState::MainMenuState() :
    onut::State<eMainMenuState>(eMainMenuState::IDLE)
{
}

void MainMenuState::init()
{
    m_fadeAnim.start(Color::Transparent, .25f);
}

void MainMenuState::update()
{
}

void MainMenuState::render()
{
    ORenderer->clear(Color::Black);
    OSB->begin();

    // Draw star background
    auto pTexBg = OGetTexture("bg.png");
    OSB->drawSprite(pTexBg, OScreenCenterf, Color::White, 0.f, OScreenHf / pTexBg->getSizef().y);

    // Draw fade
    if (m_fadeAnim.isPlaying())
    {
        OSB->drawRect(nullptr, ORectFullScreen, m_fadeAnim.get());
    }

    OSB->end();
}

bool MainMenuState::onLeaveState(eMainMenuState oldState, eMainMenuState newState)
{
    return true;
}

void MainMenuState::onEnterState(eMainMenuState newState)
{
}
