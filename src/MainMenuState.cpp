#include "MainMenuState.h"

MainMenuState::MainMenuState() :
    onut::State<eMainMenuState>(eMainMenuState::IDLE),
    m_circuitFx({OScreenWf * GOLDEN_SECOND, OScreenCenterYf})
{
}

const float INCLINE_RATIO = GOLDEN_SECOND;
float incline(float base, float pos)
{
    return base - pos * INCLINE_RATIO;
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
    m_buttons[0].setText("Campain");
    m_buttons[1].setText("Online");
    m_buttons[2].setText("Build");
    m_buttons[3].setText("Options");
    m_buttons[4].setText("Exit");

    const float BUTTON_H = m_buttons[0].getSize().y;
    const float BUTTON_SPACING = BUTTON_H * GOLDEN_RATIO;
    auto yBase = OScreenCenterYf;
    auto buttonOffsetY = (OScreenHf * GOLDEN_FIRST - 5.f * GOLDEN_FIRST * (BUTTON_SPACING + BUTTON_H)) - yBase;
    auto inclineBase = OScreenWf * GOLDEN_FIRST - 168.f - BUTTON_SPACING * GOLDEN_FIRST;
    auto showDelay = .45f;
    for (auto& button : m_buttons)
    {
        button.setPosition({incline(inclineBase, buttonOffsetY), yBase + buttonOffsetY});
        button.show(showDelay);

        buttonOffsetY += BUTTON_SPACING + button.getSize().y;
        showDelay += .2f;
    }
}

void MainMenuState::update()
{
    // Update the circuit effect
    m_circuitFx.update();

    // Buttons
    for (auto& button : m_buttons)
    {
        button.update();
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
    OSB->drawInclinedRect(nullptr, {strokeStartPos, 0, STROKE_WIDTH, m_strokeAnim.get()}, -INCLINE_RATIO, g_pal[5]);
    OSB->drawInclinedRect(nullptr, {strokeStartPos + 100 + STROKE_WIDTH * GOLDEN_FIRST * GOLDEN_FIRST, 0, STROKE_WIDTH * GOLDEN_FIRST, m_smallStrokeAnim.get()}, -INCLINE_RATIO, g_pal[4]);

    // Draw buttons
    for (auto& button : m_buttons)
    {
        button.render();
    }
    /*
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
    */
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
