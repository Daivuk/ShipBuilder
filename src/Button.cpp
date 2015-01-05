#include "Button.h"

const float     INCLINE_RATIO = GOLDEN_SECOND;
const Vector2   TEXT_OFFSET = {-32.f, 0.f};
const Vector2   TEXT_SHADOW_OFFSET = TEXT_OFFSET + Vector2{3.f, 3.f};
const Vector2   SELECTION_TEXT_OFFSET = {-16.f, 0.f};

Button::Button()
{
}

void Button::show(float delay)
{
    m_widthAnim.start(0.f, {
        OAnimWait(0.f, delay),
        {1.f, .35f, OEaseOut},
    });
    m_textAnim.start("", {
        OAnimWait("", delay + .35f),
        {m_text, .35f, OEaseOut},
    });
}

void Button::hide(float delay)
{
}

void Button::update()
{
    // Build the rect from our current position, size and animation
    m_rect = {m_position.x, m_position.y, m_size.x * m_widthAnim.get(), m_size.y};

    // Check if mouse hover
    auto mouseHover = m_rect.Grow(8.f).Contains(OMousePos);
    if (m_isSelected && !mouseHover)
    {
        m_selectionAnim.start(0.f, .15f, OEaseOut);
        m_isSelected = false;
    }
    else if (!m_isSelected && mouseHover)
    {
        m_selectionAnim.start(1.f, .05f, OEaseOut);
        m_isSelected = true;
    }
}

void Button::render()
{
    extern OPal g_pal;

    // Shadow
    auto shadowHeight = m_rect.w * GOLDEN_FIRST;
    Rect shadowRect = {m_rect.x - INCLINE_RATIO * m_rect.w, m_rect.y + m_rect.w, m_rect.z, shadowHeight};
    OSB->drawInclinedRect(nullptr, shadowRect, -INCLINE_RATIO, {0, 0, 0, .3f});

    // Button background
    OSB->drawInclinedRect(nullptr, m_rect, -INCLINE_RATIO, g_pal[7]);

    // Text
    auto m = OGetBMFont("ethno20.fnt")->measure("Campaign");
    OGetBMFont("ethno20.fnt")->draw<ORight>(m_textAnim.get(), m_rect.Right() + TEXT_SHADOW_OFFSET + m_selectionAnim.get() * SELECTION_TEXT_OFFSET, g_pal[3]);
    OGetBMFont("ethno20.fnt")->draw<ORight>(m_textAnim.get(), m_rect.Right() + TEXT_OFFSET + m_selectionAnim.get() * SELECTION_TEXT_OFFSET, g_pal[0]);

    // Selection
    OSB->drawInclinedRect(nullptr, {m_rect.x - 22.f + 17.f - m_selectionAnim.get()* 17.f, m_rect.y, m_selectionAnim.get()* 17.f, m_rect.w}, -INCLINE_RATIO, g_pal[2]);
    OSB->drawInclinedRect(nullptr, {m_rect.x + m_rect.z + 5.f, m_rect.y, m_selectionAnim.get()* 17.f, m_rect.w}, -INCLINE_RATIO, g_pal[2]);
}

void Button::setSize(const Vector2& size)
{
    m_size = size;
}

void Button::setPosition(const Vector2& position)
{
    m_position = position;
}

void Button::setText(const std::string& text)
{
    m_text = text;
}
