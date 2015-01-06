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
    // Start fade in anims
    m_fadeAnim.start(Color::Transparent, .25f);

    // Strokes
    m_strokeAnim.start(OScreenHf, .4f, OEaseOut);
    m_smallStrokeAnim.start({
        OAnimWait(0.f, .25f),
        {OScreenHf, .5f, OEaseOut},
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
    decltype(m_selection) i = 0;
    for (auto& button : m_buttons)
    {
        button.setPosition({incline(inclineBase, buttonOffsetY), yBase + buttonOffsetY});
        button.show(showDelay);
        button.setCallback([this, i]{
            m_selection = i;
            changeState(eMainMenuState::FADE_OUT);
        });

        buttonOffsetY += BUTTON_SPACING + button.getSize().y;
        showDelay += .15f;
        ++i;
    }
}

void MainMenuState::update()
{
    // Update the circuit effect
    m_circuitFx.update();

    // Buttons
    for (auto& button : m_buttons)
    {
        if (button.update())
        {
            break;
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
    OSB->drawInclinedRect(nullptr, {strokeStartPos, 0, STROKE_WIDTH, m_strokeAnim.get()}, -INCLINE_RATIO, g_pal[5]);
    OSB->drawInclinedRect(nullptr, {strokeStartPos + 100 + STROKE_WIDTH * GOLDEN_FIRST * GOLDEN_FIRST, 0, STROKE_WIDTH * GOLDEN_FIRST, m_smallStrokeAnim.get()}, -INCLINE_RATIO, g_pal[4]);

    // Draw buttons
    for (auto& button : m_buttons)
    {
        button.render();
    }

    // Draw fade
    if (m_fadeAnim.get().A() > 0.f)
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
    if (newState == eMainMenuState::FADE_OUT)
    {
        // Start the hide animation on buttons
        for (auto& button : m_buttons)
        {
            button.hide();
        }
        m_strokeAnim.start(0.f, .20f, OEaseIn);
        m_smallStrokeAnim.start({
            OAnimWait(m_smallStrokeAnim.get(), .05f),
            {0.f, .25f, OEaseIn},
        });
        m_fadeAnim.start({Color::Black, .25f, OLinear, [this]{
            switch (m_selection)
            {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    PostQuitMessage(0);
                    break;
            }
        }});
    }
}
