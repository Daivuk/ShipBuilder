#include "InitialLoadingState.h"
#include "states.h"

InitialLoadingState::InitialLoadingState() :
    onut::State<eInitialLoadingState>(eInitialLoadingState::FADE_IN)
{
}

void InitialLoadingState::init()
{
    m_fadeAnim.start({Color::Transparent, .25f, OLinear, [this]
    {
        changeState(eInitialLoadingState::LOADING);
    }});
    m_boxAnim.start(360.f, 1.f, OLinear, OLoop);
}

void InitialLoadingState::render()
{
    ORenderer->clear();
    OSB->begin();
    OSB->drawSprite(nullptr, OScreenCenterf, Color::White, m_boxAnim.get(), 64.f);
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
    OAsync([this]
    {
        OSync([this]
        {
            changeState(eInitialLoadingState::FADE_OUT);
        });
    });
}
