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
    extern OPal g_pal;

    ORenderer->clear(Color::Black);
    OSB->begin();

    // Draw star background
    auto pTexBg = OGetTexture("bg.png");
    OSB->drawRect(pTexBg, ORectFullScreen.Fit(pTexBg->getSizef()), g_pal[7]);

    // Draw fade
    if (m_fadeAnim.isPlaying())
    {
        OSB->drawRect(nullptr, ORectFullScreen, m_fadeAnim.get());
    }

    OSB->end();

    onut::drawPal(g_pal);
}

bool MainMenuState::onLeaveState(eMainMenuState oldState, eMainMenuState newState)
{
    return true;
}

void MainMenuState::onEnterState(eMainMenuState newState)
{
}
