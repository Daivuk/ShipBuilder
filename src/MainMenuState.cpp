#include "MainMenuState.h"

MainMenuState::MainMenuState() :
    onut::State<eMainMenuState>(eMainMenuState::IDLE),
    m_circuitFx({OScreenWf * GOLDEN_SECOND, OScreenCenterYf})
{
}

void MainMenuState::init()
{
    extern OPal g_pal;

    // Start fade in anims
    m_fadeAnim.start(Color::Transparent, .25f);

    // Strokes
    m_strokeAnim.start(OScreenHf, .5f, OEaseOut);
    m_smallStrokeAnim.start({
        OAnimWait(0.f, .25f),
        {OScreenHf, .6f, OEaseOut},
    });

    // Buttons
    m_btnAnim[0].start(0.f, {
        OAnimWait(0.f, .45f),
        {209.f, .35f, OEaseOut},
    });
    m_btnAnim[1].start(0.f, {
        OAnimWait(0.f, .65f),
        {209.f, .35f, OEaseOut},
    });
    m_btnAnim[2].start(0.f, {
        OAnimWait(0.f, .85f),
        {209.f, .35f, OEaseOut},
    });

    // Button shadows
    m_btnShadows[0].start(Color::Transparent, {
        OAnimWait(Color::Transparent, .45f),
        {g_pal[4], .35f, OEaseOut},
    });
    m_btnShadows[1].start(Color::Transparent, {
        OAnimWait(Color::Transparent, .65f),
        {g_pal[4], .35f, OEaseOut},
    });
    m_btnShadows[2].start(Color::Transparent, {
        OAnimWait(Color::Transparent, .85f),
        {g_pal[4], .35f, OEaseOut},
    });

    // Button texts
    m_btnText[0].start("", {
        OAnimWait("", .8f),
        {"Play", .35f, OEaseOut},
    });
    m_btnText[1].start("", {
        OAnimWait("", 1.f),
        {"Build", .35f, OEaseOut},
    });
    m_btnText[2].start("", {
        OAnimWait("", 1.2f),
        {"Quit", .35f, OEaseOut},
    });

    // No button selected by default
    m_btnSelection[0] = 0.f;
    m_btnSelection[1] = 0.f;
    m_btnSelection[2] = 0.f;
}

const float inclineRatio = 64.f / 80.f;
float incline(float base, float pos)
{
    return base - pos * inclineRatio;
}

void MainMenuState::update()
{
    // Update the circuit effect
    m_circuitFx.update();

    // Buttons mouse hover
    auto lastSelection = m_selection;
    m_selection = -1;

    auto inclineBase = OScreenWf * GOLDEN_FIRST;
    Rect btnRects[3];
    btnRects[0] = {incline(inclineBase, -19.f - 80.f) - 190.f, OScreenCenterYf - 19.f - 80.f, m_btnAnim[0].get(), 39};
    btnRects[1] = {incline(inclineBase, -19.f) - 190.f, OScreenCenterYf - 19.f, m_btnAnim[1].get(), 39};
    btnRects[2] = {incline(inclineBase, -19.f + 80.f) - 190.f, OScreenCenterYf - 19.f + 80.f, m_btnAnim[2].get(), 39};

    for (int i = 0; i < 3; ++i)
    {
        if (btnRects[i].Contains(OMousePos))
        {
            m_selection = i;
        }
    }

    if (lastSelection != m_selection)
    {
        if (lastSelection != -1)
        {
            m_btnSelection[lastSelection].start(0.f, .15f, OEaseOut);
        }
        if (m_selection != -1)
        {
            m_btnSelection[m_selection].start(1.f, .05f, OEaseOut);
        }
    }
}

void MainMenuState::render()
{
    extern OPal g_pal;

    ORenderer->clear(Color::Black);
    OSB->begin();

    // Draw star background
    auto pTexBg = OGetTexture("bg.png");
    OSB->drawRect(pTexBg, ORectFullScreen.Fit(pTexBg->getSizef()), g_pal[7]);

    OSB->end();

    // Circuits
    m_circuitFx.render();

    OSB->begin();

    // Draw stroke
    const float STROKE_WIDTH = 100.f;
    auto inclineBase = OScreenWf * GOLDEN_FIRST;
    auto strokeStartPos = incline(inclineBase - 168.f, -OScreenCenterYf);
    OSB->drawInclinedRect(nullptr, {strokeStartPos, 0, STROKE_WIDTH, m_strokeAnim.get()}, -inclineRatio, g_pal[5]);
    OSB->drawInclinedRect(nullptr, {strokeStartPos + 110, 0, STROKE_WIDTH * GOLDEN_FIRST, m_smallStrokeAnim.get()}, -inclineRatio, g_pal[5]);

    // Draw buttons and their shadows
    OSB->drawInclinedRect(nullptr, {incline(inclineBase - 168.f, 20.f - 80.f), OScreenCenterYf + 20.f - 80.f, STROKE_WIDTH, 11}, -inclineRatio, m_btnShadows[0].get());
    OSB->drawInclinedRect(nullptr, {incline(inclineBase - 168.f, 20.f - 80.f) + 110, OScreenCenterYf + 20.f - 80.f, STROKE_WIDTH * GOLDEN_FIRST, 11}, -inclineRatio, m_btnShadows[0].get());
    OSB->drawInclinedRect(nullptr, {incline(inclineBase, -19.f - 80.f) - 190.f, OScreenCenterYf - 19.f - 80.f, m_btnAnim[0].get(), 39}, -inclineRatio, g_pal[7]);

    OSB->drawInclinedRect(nullptr, {incline(inclineBase - 168.f, 20.f), OScreenCenterYf + 20.f, STROKE_WIDTH, 11}, -inclineRatio, m_btnShadows[1].get());
    OSB->drawInclinedRect(nullptr, {incline(inclineBase - 168.f, 20.f) + 110, OScreenCenterYf + 20.f, STROKE_WIDTH * GOLDEN_FIRST, 11}, -inclineRatio, m_btnShadows[1].get());
    OSB->drawInclinedRect(nullptr, {incline(inclineBase, -19.f) - 190.f, OScreenCenterYf - 19.f, m_btnAnim[1].get(), 39}, -inclineRatio, g_pal[7]);

    OSB->drawInclinedRect(nullptr, {incline(inclineBase - 168.f, 20.f + 80.f), OScreenCenterYf + 20.f + 80.f, STROKE_WIDTH, 11}, -inclineRatio, m_btnShadows[2].get());
    OSB->drawInclinedRect(nullptr, {incline(inclineBase - 168.f, 20.f + 80.f) + 110, OScreenCenterYf + 20.f + 80.f, STROKE_WIDTH * GOLDEN_FIRST, 11}, -inclineRatio, m_btnShadows[2].get());
    OSB->drawInclinedRect(nullptr, {incline(inclineBase, -19.f + 80.f) - 190.f, OScreenCenterYf - 19.f + 80.f, m_btnAnim[2].get(), 39}, -inclineRatio, g_pal[7]);

    // Draw text
    OGetBMFont("ethno32.fnt")->draw<ORight>(m_btnText[0].get(), {incline(inclineBase, -80.f) + 4.f - m_btnSelection[0].get() * 16.f, OScreenCenterYf - 80.f + 4.f}, g_pal[3]);
    OGetBMFont("ethno32.fnt")->draw<ORight>(m_btnText[0].get(), {incline(inclineBase, -80.f) - m_btnSelection[0].get() * 16.f, OScreenCenterYf - 80.f}, g_pal[0]);

    OGetBMFont("ethno32.fnt")->draw<ORight>(m_btnText[1].get(), {incline(inclineBase, 0.f) + 4.f - m_btnSelection[1].get() * 16.f, OScreenCenterYf + 4.f}, g_pal[3]);
    OGetBMFont("ethno32.fnt")->draw<ORight>(m_btnText[1].get(), {incline(inclineBase, 0.f) - m_btnSelection[1].get() * 16.f, OScreenCenterYf}, g_pal[0]);

    OGetBMFont("ethno32.fnt")->draw<ORight>(m_btnText[2].get(), {incline(inclineBase, 80.f) + 4.f - m_btnSelection[2].get() * 16.f, OScreenCenterYf + 80.f + 4.f}, g_pal[3]);
    OGetBMFont("ethno32.fnt")->draw<ORight>(m_btnText[2].get(), {incline(inclineBase, 80.f) - m_btnSelection[2].get() * 16.f, OScreenCenterYf + 80.f}, g_pal[0]);

    // Draw selected buttons
    OSB->drawInclinedRect(nullptr, {incline(inclineBase, -19.f - 80.f) - 190.f - 22.f + 17.f - m_btnSelection[0].get() * 17.f, OScreenCenterYf - 19.f - 80.f, m_btnSelection[0].get()* 17.f, 39}, -inclineRatio, g_pal[2]);
    OSB->drawInclinedRect(nullptr, {incline(inclineBase, -19.f - 80.f) - 190.f + 214.f, OScreenCenterYf - 19.f - 80.f, m_btnSelection[0].get()* 17.f, 39}, -inclineRatio, g_pal[2]);

    OSB->drawInclinedRect(nullptr, {incline(inclineBase, -19.f) - 190.f - 22.f + 17.f - m_btnSelection[1].get()* 17.f, OScreenCenterYf - 19.f, m_btnSelection[1].get()* 17.f, 39}, -inclineRatio, g_pal[2]);
    OSB->drawInclinedRect(nullptr, {incline(inclineBase, -19.f) - 190.f + 214.f, OScreenCenterYf - 19.f, m_btnSelection[1].get()* 17.f, 39}, -inclineRatio, g_pal[2]);

    OSB->drawInclinedRect(nullptr, {incline(inclineBase, -19.f + 80.f) - 190.f - 22.f + 17.f - m_btnSelection[2].get()* 17.f, OScreenCenterYf - 19.f + 80.f, m_btnSelection[2].get()* 17.f, 39}, -inclineRatio, g_pal[2]);
    OSB->drawInclinedRect(nullptr, {incline(inclineBase, -19.f + 80.f) - 190.f + 214.f, OScreenCenterYf - 19.f + 80.f, m_btnSelection[2].get()* 17.f, 39}, -inclineRatio, g_pal[2]);

    // Draw fade
    if (m_fadeAnim.isPlaying())
    {
        OSB->drawRect(nullptr, ORectFullScreen, m_fadeAnim.get());
    }

    OSB->end();

    //    onut::drawPal(g_pal, OGetBMFont("ethno16.fnt"));
}

bool MainMenuState::onLeaveState(eMainMenuState oldState, eMainMenuState newState)
{
    return true;
}

void MainMenuState::onEnterState(eMainMenuState newState)
{
}
