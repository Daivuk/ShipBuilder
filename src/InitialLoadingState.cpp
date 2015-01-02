#include "InitialLoadingState.h"
#include "states.h"

InitialLoadingState::InitialLoadingState() :
    onut::State<eInitialLoadingState>(eInitialLoadingState::FADE_IN)
{
}

void InitialLoadingState::init()
{
    // Start our animations
    m_boxAnim.start(360.f, 1.f, OLinear, OLoop);
    m_fadeAnim.start({Color::Transparent, .25f, OLinear, [this]
    {
        changeState(eInitialLoadingState::LOADING);
    }});
}

void InitialLoadingState::render()
{
    ORenderer->clear(Color::Black);

    OSB->begin();

    // Star background
    if (m_bgFadeAnim.get().A() > 0.f)
    {
        auto pTexBg = OGetTexture("bg.png");
        OSB->drawSprite(pTexBg, OScreenCenterf, m_bgFadeAnim.get(), 0.f, OScreenHf / pTexBg->getSizef().y);
    }

    // Spinning box
    OSB->drawSprite(nullptr, OScreenCenterf, Color::White, m_boxAnim.get(), 64.f);

    // Fade
    OSB->drawRect(nullptr, ORectFullScreen, m_fadeAnim.get());

    OSB->end();
}

void InitialLoadingState::onEnterState(eInitialLoadingState newState)
{
    if (newState == eInitialLoadingState::LOADING)
    {
        startLoading();
    }
    else if (newState == eInitialLoadingState::FADE_OUT)
    {
        m_fadeAnim.start({Color::Black, .25f, OLinear, [this]
        {
            g_stateManager.changeState(eGlobalState::MAIN_MENU);
        }});
    }
}

void InitialLoadingState::startLoading()
{
    OSequencialWork(
        [this]{
            // Load our background first. It's a big picture
            OGetTexture("bg.png");
        }, 
        [this]{
            // Background is done loading, fade it in the loading screen.
            m_bgFadeAnim.start(Color::White, 1.f, OEaseOut);
        }, 
        [this]{
            // Load more stuff
        }, 
        [this]{
            // Finished loading, fade out
            changeState(eInitialLoadingState::FADE_OUT);
        });
}
