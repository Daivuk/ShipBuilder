#pragma once
#include "onut.h"

enum class eInitialLoadingState
{
    FADE_IN,
    LOADING,
    FADE_OUT
};

class InitialLoadingState : public onut::State < eInitialLoadingState >
{
public:
    InitialLoadingState();
    virtual ~InitialLoadingState() {}

    void init() override;
    void update() override;
    void render() override;

protected:
    void onEnterState(eInitialLoadingState newState) override;

private:
    void startLoading();
    void startBoxAnim();
    void loadAllAssets();

    OAnimc  m_fadeAnim = Color::Black;
    OAnimf  m_boxAnim = 45.f;
    OAnimf  m_boxAnim2 = 0.f;
    OAnimc  m_bgFadeAnim = Color::Transparent;
    OAnimc  m_fntFadeAnim = Color::Transparent;
};
