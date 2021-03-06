#include "MainMenuState.h"
#include "states.h"

const float INCLINE_RATIO = GOLDEN_SECOND;
float incline(float base, float pos)
{
    return base - pos * INCLINE_RATIO;
}

MainMenuState::MainMenuState() :
    onut::State<eMainMenuState>(eMainMenuState::IDLE),
    m_circuitFx({OScreenWf * GOLDEN_SECOND, OScreenCenterYf}),
    m_uiContext({OScreenWf, OScreenHf}),
    m_uiScreen("../../assets/ui/main.json")
{
    m_uiContext.addStyle("RedButton", [](const onut::UIControl* pControl, const onut::sUIRect& rect)
    {
        OSB->drawRect(nullptr, onut::UI2Onut(rect), {1, 0, 0, 1});
    });
    m_uiContext.addStyle("AngledButton", [this](const onut::UIControl* pControl, const onut::sUIRect& rect)
    {
        auto pButton = dynamic_cast<const onut::UIButton*>(pControl);
        switch (pControl->getState(m_uiContext))
        {
            case onut::eUIState::NORMAL:
                OSB->drawInclinedRect(nullptr, onut::UI2Onut(rect), -INCLINE_RATIO, {.75f, .75f, .75f, 1});
                break;
            case onut::eUIState::HOVER:
                OSB->drawInclinedRect(nullptr, onut::UI2Onut(rect), -INCLINE_RATIO, {1, 1, 1, 1});
                break;
            case onut::eUIState::DOWN:
                OSB->drawInclinedRect(nullptr, {rect.position.x + 2, rect.position.y + 1, rect.size.x, rect.size.y}, -INCLINE_RATIO, {.5f, .5f, .5f, 1});
                break;
            case onut::eUIState::DISABLED:
                OSB->drawInclinedRect(nullptr, onut::UI2Onut(rect), -INCLINE_RATIO, {.25f, .25f, .25f, 1});
                break;
        }
        OGetBMFont("ethno20.fnt")->draw<ORight>(pButton->getCaption(), onut::UI2Onut(rect).Right(32), Color::Black);
    });

    m_uiScreen.getChild("btn4")->onClick = [this](const onut::UIControl* pControl, const onut::UIMouseEvent& evt){
        m_selection = 0;
        changeState(eMainMenuState::FADE_OUT);
    };
}

void MainMenuState::init()
{
    // Start fade in anims
    m_fadeAnim.start(Color::Transparent, .25f);

    // Title
    m_titleAnim.start(1.f, {
        OAnimWait(1.f, .5f),
        {0.f, .5f, OEaseOut}
    });

    // Strokes
    m_strokeAnim.start(OScreenHf, .4f, OEaseOut);
    m_smallStrokeAnim.start({
        OAnimWait(0.f, .25f),
        {OScreenHf, .5f, OEaseOut},
    });

    // Buttons
    m_buttons[0].setText("Solo");
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
    m_uiScreen.update(m_uiContext, {OMousePos.x, OMousePos.y}, OInput->isStateDown(DIK_MOUSEB1));
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

    // Logo
    OGetBMFont("ethno64.fnt")->draw<OBottomRight>("Ship Builder", ORectFullScreen.BottomRight(64.f * GOLDEN_SECOND) + 
                                                  Vector2{m_titleAnim.get() * 100.f + 4.f, 4.f},
                                                  onut::lerp(g_pal[3], Color::Transparent, m_titleAnim.get()));
    OGetBMFont("ethno64.fnt")->draw<OBottomRight>("Ship Builder", ORectFullScreen.BottomRight(64.f * GOLDEN_SECOND) +
                                                  Vector2{m_titleAnim.get() * 100.f + 0.f, 0.f},
                                                  onut::lerp(g_pal[0], Color::Transparent, m_titleAnim.get()));

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

    m_uiScreen.render(m_uiContext);
    
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
        m_titleAnim.start(1.f, .15f, OEaseIn);
        m_fadeAnim.start({Color::Black, .25f, OLinear, [this]{
            switch (m_selection)
            {
                case 0:
                    g_stateManager.changeState(eGlobalState::PLAY);
                    break;
                case 1:
                    break;
                case 2:
                    g_stateManager.changeState(eGlobalState::SHIP_BUILDER);
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
