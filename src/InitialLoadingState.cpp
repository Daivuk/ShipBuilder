#include <cmath>
#include "InitialLoadingState.h"
#include "states.h"

InitialLoadingState::InitialLoadingState() :
    onut::State<eInitialLoadingState>(eInitialLoadingState::FADE_IN)
{
}

void InitialLoadingState::init()
{
    // Start our animations
    startBoxAnim();
    m_fadeAnim.start({Color::Transparent, .25f, OLinear, [this]
    {
        changeState(eInitialLoadingState::LOADING);
    }});
}

void InitialLoadingState::startBoxAnim()
{
    auto rnd = onut::randi(-2, 2);
    switch (rnd)
    {
        case -1:
        {
            m_boxAnim.start({m_boxAnim.get() - 2.f * 90.f, .5f, OEaseOut});
            m_boxAnim2.start(0.f,
            {
                OAnimWait(0.f, .4f),
                {1.f, .1f, OEaseIn},
                {0.f, .1f, OEaseOut}
            });
            break;
        }
        case -2:
        {
            m_boxAnim.start({m_boxAnim.get() -1.f * 90.f, .5f, OEaseOut});
            m_boxAnim2.start(0.f,
            {
                OAnimWait(0.f, .4f),
                {1.f, .1f, OEaseIn},
                {0.f, .1f, OEaseOut}
            });
            break;
        }
        case 0:
        {
            m_boxAnim.start({m_boxAnim.get(), .25f, OEaseOut});
            break;
        }
        case 1:
        {
            m_boxAnim.start({m_boxAnim.get() + 1.f * 90.f, .5f, OEaseOut});
            m_boxAnim2.start(0.f,
            {
                OAnimWait(0.f, .4f),
                {1.f, .1f, OEaseIn},
                {0.f, .1f, OEaseOut}
            });
            break;
        }
        case 2:
        {
            m_boxAnim.start({m_boxAnim.get() + 2.f * 90.f, .5f, OEaseOut});
            m_boxAnim2.start(0.f,
            {
                OAnimWait(0.f, .4f),
                {1.f, .1f, OEaseIn},
                {0.f, .1f, OEaseOut}
            });
            break;
        }
    }
}

void InitialLoadingState::update()
{
    if (!m_boxAnim.isPlaying())
    {
        startBoxAnim();
    }
}

void InitialLoadingState::render()
{
    extern OPal g_pal;

    ORenderer->clear(Color::Black);
    OSB->begin();

    // Star background
    if (m_bgFadeAnim.get().A() > 0.f)
    {
        auto pTexBg = OGetTexture("bg.png");
        OSB->drawRect(pTexBg, ORectFullScreen.Fit(pTexBg->getSizef()), m_bgFadeAnim.get());
    }

    // Spinning loading boxes
    const auto fadeT = m_fadeAnim.get().A();
    const auto scale = 1.f / (std::abs(std::sin(DirectX::XMConvertToRadians(m_boxAnim.get()))) + std::abs(std::cos(DirectX::XMConvertToRadians(m_boxAnim.get()))));
    const auto borderW = 4.f;
    const auto yPos = OScreenHf * GOLDEN_SECOND;

    // Streaks
    Rect centerRect = {OScreenCenterXf, yPos, 0, 0};
    OSB->drawRectWithColors(nullptr, 
                            centerRect.Right({0, 0, 256.f, borderW * m_boxAnim2.get()}),
                            OGradientH(Color::Transparent, g_pal[0]));
    OSB->drawRectWithColors(nullptr, 
                            centerRect.Left({0, 0, 256.f, borderW * m_boxAnim2.get()}),
                            OGradientH(g_pal[0], Color::Transparent));

    OSB->drawRectWithColors(nullptr,
                            Rect{OScreenCenterXf - (32.f + 32.f + 8.f), yPos, 0, 0}.Bottom({0, 0, borderW / 2.f * m_boxAnim2.get(), 32.f}),
                            OGradientV(Color::Transparent, g_pal[0]));
    OSB->drawRectWithColors(nullptr,
                            Rect{OScreenCenterXf + (32.f + 32.f + 8.f), yPos, 0, 0}.Bottom({0, 0, borderW / 2.f * m_boxAnim2.get(), 32.f}),
                            OGradientV(Color::Transparent, g_pal[0]));
    OSB->drawRectWithColors(nullptr,
                            Rect{OScreenCenterXf - (32.f + 32.f + 8.f), yPos, 0, 0}.Top({0, 0, borderW / 2.f * m_boxAnim2.get(), 32.f}),
                            OGradientV(g_pal[0], Color::Transparent));
    OSB->drawRectWithColors(nullptr,
                            Rect{OScreenCenterXf + (32.f + 32.f + 8.f), yPos, 0, 0}.Top({0, 0, borderW / 2.f * m_boxAnim2.get(), 32.f}),
                            OGradientV(g_pal[0], Color::Transparent));

    OSB->drawRectWithColors(nullptr,
                            Rect{OScreenCenterXf - (32.f + 16.f), yPos, 0, 0}.Bottom({0, 0, borderW / 2.f * m_boxAnim2.get(), 64.f}),
                            OGradientV(Color::Transparent, g_pal[1]));
    OSB->drawRectWithColors(nullptr,
                            Rect{OScreenCenterXf + (32.f + 16.f), yPos, 0, 0}.Bottom({0, 0, borderW / 2.f * m_boxAnim2.get(), 64.f}),
                            OGradientV(Color::Transparent, g_pal[1]));
    OSB->drawRectWithColors(nullptr,
                            Rect{OScreenCenterXf - (32.f + 16.f), yPos, 0, 0}.Top({0, 0, borderW / 2.f * m_boxAnim2.get(), 64.f}),
                            OGradientV(g_pal[1], Color::Transparent));
    OSB->drawRectWithColors(nullptr,
                            Rect{OScreenCenterXf + (32.f + 16.f), yPos, 0, 0}.Top({0, 0, borderW / 2.f * m_boxAnim2.get(), 64.f}),
                            OGradientV(g_pal[1], Color::Transparent));

    OSB->drawRectWithColors(nullptr,
                            Rect{OScreenCenterXf, yPos, 0, 0}.Bottom({0, 0, borderW / 2.f * m_boxAnim2.get(), 128.f}),
                            OGradientV(Color::Transparent, g_pal[2]));
    OSB->drawRectWithColors(nullptr,
                            Rect{OScreenCenterXf, yPos, 0, 0}.Top({0, 0, borderW / 2.f * m_boxAnim2.get(), 128.f}),
                            OGradientV(g_pal[2], Color::Transparent));

    // Outlines
    OSB->drawSprite(nullptr, {
        onut::lerp<float>(OScreenCenterXf + (32.f + 32.f + 8.f), OScreenWf, fadeT),
        yPos}, g_pal[0] * m_boxAnim2.get(), m_boxAnim.get(), 16.f * scale);
    OSB->drawSprite(nullptr, {
        onut::lerp<float>(OScreenCenterXf + (32.f + 16.f), OScreenWf * .75f, fadeT),
        yPos}, g_pal[1] * m_boxAnim2.get(), m_boxAnim.get(), 32.f * scale);
    OSB->drawSprite(nullptr, {OScreenCenterXf, yPos}, g_pal[2] * m_boxAnim2.get(), m_boxAnim.get(), 64.f * scale);
    OSB->drawSprite(nullptr, {
        onut::lerp<float>(OScreenCenterXf - (32.f + 16.f), OScreenWf * .25f, fadeT),
        yPos}, g_pal[1] * m_boxAnim2.get(), m_boxAnim.get(), 32.f * scale);
    OSB->drawSprite(nullptr, {
        onut::lerp<float>(OScreenCenterXf - (32.f + 32.f + 8.f), 0.f, fadeT),
        yPos}, g_pal[0] * m_boxAnim2.get(), m_boxAnim.get(), 16.f * scale);

    // Inner boxes
    OSB->drawSprite(nullptr, {
        onut::lerp<float>(OScreenCenterXf + (32.f + 32.f + 8.f), OScreenWf, fadeT),
        yPos}, g_pal[6], m_boxAnim.get(), 16.f * scale - borderW);
    OSB->drawSprite(nullptr, {
        onut::lerp<float>(OScreenCenterXf + (32.f + 16.f), OScreenWf * .75f, fadeT),
        yPos}, g_pal[5], m_boxAnim.get(), 32.f * scale - borderW);
    OSB->drawSprite(nullptr, {OScreenCenterXf, yPos}, g_pal[4], m_boxAnim.get(), 64.f * scale - borderW);
    OSB->drawSprite(nullptr, {
        onut::lerp<float>(OScreenCenterXf - (32.f + 16.f), OScreenWf * .25f, fadeT),
        yPos}, g_pal[5], m_boxAnim.get(), 32.f * scale - borderW);
    OSB->drawSprite(nullptr, {
        onut::lerp<float>(OScreenCenterXf - (32.f + 32.f + 8.f), 0.f, fadeT),
        yPos}, g_pal[6], m_boxAnim.get(), 16.f * scale - borderW);

    // Fade
    OSB->drawRect(nullptr, ORectFullScreen, m_fadeAnim.get());

    OSB->end();

    onut::drawPal(g_pal);
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
            extern OPal g_pal;
            m_bgFadeAnim.start(g_pal[7], 1.f, OEaseOut);
        }, 
        [this]{
            // Load more stuff
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }, 
        [this]{
            // Finished loading, fade out
            changeState(eInitialLoadingState::FADE_OUT);
        });
}
