#include "BuildState.h"

BuildState::BuildState() :
    onut::State<eBuildState>(eBuildState::IDLE)/*,
    m_uiScreen({OScreenWf, OScreenHf})*/
{
    {
        //auto pBtnSave = new onut::UIButton(&m_uiScreen, 
    }
}

BuildState::~BuildState()
{
}

void BuildState::init()
{
    m_fadeAnim.start(Color::Transparent, .25f);
}

void BuildState::update()
{
    // Update UIs
  //  m_uiScreen.updateScreen({OMousePos.x, OMousePos.y});

    // Navigate (Zoom and pan)
    if (OInput->getStateValue(DIK_MOUSEZ) > 0.f)
    {
        m_zoomLevel += 2;
        if (m_zoomLevel > 32) m_zoomLevel = 32;
    }
    else if (OInput->getStateValue(DIK_MOUSEZ) < 0.f)
    {
        m_zoomLevel -= 2;
        if (m_zoomLevel < 0) m_zoomLevel = 0;
    }

    float targetZoomf = static_cast<float>(m_zoomLevel);
    if (m_zoomf < targetZoomf)
    {
        m_zoomf += (targetZoomf - m_zoomf) * ODT * 10.f;
        if (m_zoomf > targetZoomf) m_zoomf = targetZoomf;
    }
    else if (m_zoomf > targetZoomf)
    {
        m_zoomf += (targetZoomf - m_zoomf) * ODT * 10.f;
        if (m_zoomf < targetZoomf) m_zoomf = targetZoomf;
    }
    m_zoomf = std::max<float>(1.f, m_zoomf);

    // Setup the plan camera and zoom
    m_viewProj = ORenderer->build2DCameraOffCenter(m_camPos, m_zoomf);;
    m_viewProj *= Matrix::CreateScale(1.f, -1.f, 1.f);
}

void BuildState::render()
{
    ORenderer->clear(Color::Black);

    // Grid
    ORenderer->set2DCamera(m_viewProj);
    drawGrid();
    ORenderer->set2DCamera(Vector2::Zero);

    // Draw UI
    OSB->begin();
 //   m_uiScreen.renderScreen();

    // Fade in/out
    if (m_fadeAnim.get().A() > 0.f)
    {
        OSB->drawRect(nullptr, ORectFullScreen, m_fadeAnim.get());
    }
    OSB->end();

    extern OPal g_pal;
    onut::drawPal(g_pal, OGetBMFont("ethno16.fnt"));
}

bool BuildState::onLeaveState(eBuildState oldState, eBuildState newState)
{
    return true;
}

void BuildState::onEnterState(eBuildState newState)
{
}

void BuildState::drawGrid()
{
    extern OPal g_pal;
    auto mainColor = g_pal[8] * .5f;
    auto secondaryColor = g_pal[7] * .25f;

    auto density = m_zoomf / 8.f;
    int secondarySteps = 1;
    while (density < 1.f)
    {
        secondarySteps *= 4;
        density *= 4.f;
    }
    int mainSteps = secondarySteps * 4;
    density -= 1.f;
    if (density < 0.f) density = 0.f;
    if (density > 2.f) density = 2.f;
    secondaryColor = onut::lerp(Color::Transparent, secondaryColor, std::min<float>(1.f, density));
    secondaryColor = onut::lerp(secondaryColor, mainColor, std::max<float>(0.f, density - 1.f));

    int bounds[4];
    bounds[0] = static_cast<int>(roundf(m_camPos.x - OScreenCenterXf / m_zoomf)) - 1;
    bounds[1] = static_cast<int>(roundf(m_camPos.x + OScreenCenterXf / m_zoomf)) + 1;
    bounds[2] = static_cast<int>(roundf(m_camPos.y - OScreenCenterYf / m_zoomf)) - 1;
    bounds[3] = static_cast<int>(roundf(m_camPos.y + OScreenCenterYf / m_zoomf)) + 1;
    bounds[0] -= mainSteps - std::abs(bounds[0] % mainSteps);
    bounds[2] -= mainSteps - std::abs(bounds[2] % mainSteps);

    OPB->begin(onut::ePrimitiveType::LINES);
    // Horizontal
    for (auto i = bounds[0]; i <= bounds[1]; i += secondarySteps)
    {
        if (i % mainSteps)
        {
            OPB->draw({static_cast<float>(i), static_cast<float>(bounds[2])}, secondaryColor);
            OPB->draw({static_cast<float>(i), static_cast<float>(bounds[3])}, secondaryColor);
        }
        else
        {
            OPB->draw({static_cast<float>(i), static_cast<float>(bounds[2])}, mainColor);
            OPB->draw({static_cast<float>(i), static_cast<float>(bounds[3])}, mainColor);
        }
    }
    // Vertical
    for (auto j = bounds[2]; j <= bounds[3]; j += secondarySteps)
    {
        if (j % mainSteps)
        {
            OPB->draw({static_cast<float>(bounds[0]), static_cast<float>(j)}, secondaryColor);
            OPB->draw({static_cast<float>(bounds[1]), static_cast<float>(j)}, secondaryColor);
        }
        else
        {
            OPB->draw({static_cast<float>(bounds[0]), static_cast<float>(j)}, mainColor);
            OPB->draw({static_cast<float>(bounds[1]), static_cast<float>(j)}, mainColor);
        }
    }
    OPB->end();
}
