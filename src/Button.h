#pragma once
#include "onut.h"
#include <functional>

class Button
{
public:
    Button();

    bool update();
    void render();

    void show(float delay = 0.f);
    void hide(float delay = 0.f);

    void setSize(const Vector2& size);
    void setPosition(const Vector2& position);
    void setText(const std::string& text);
    void setCallback(const std::function<void()>& callback);

    const Vector2& getSize() const { return m_size; }

private:
    OAnimf                  m_widthAnim = 0.f;
    OAnimc                  m_shadowColorAnim = Color::Transparent;
    OAnimStr                m_textAnim;
    OAnimf                  m_selectionAnim = 0.f;
    bool                    m_isSelected = false;
    Vector2                 m_position;
    Vector2                 m_size = {20.f * GOLDEN_RATIO * GOLDEN_RATIO * 4.f, 20.f * GOLDEN_RATIO};
    std::string             m_text;
    Rect                    m_rect;
    std::function<void()>   m_callback;
};
