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

    void init() override;
    void render() override;

protected:
    void onEnterState(eInitialLoadingState newState) override;

private:
    void startLoading();

    OAnimc  m_fadeAnim = Color::Black;
    OAnimf  m_boxAnim = 45.f;
};
