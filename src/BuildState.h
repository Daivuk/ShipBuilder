#pragma once
#include "onut.h"

enum eBuildState
{
    IDLE
};

class BuildState : public onut::State < eBuildState >
{
public:
    BuildState();
    virtual ~BuildState();

    void init();
    void update();
    void render();

protected:        
    bool onLeaveState(eBuildState oldState, eBuildState newState) override;
    void onEnterState(eBuildState newState) override;

private:
    void drawGrid();

    OAnimc          m_fadeAnim = Color::Black;
    Vector2         m_camPos;
    Matrix          m_viewProj;
    float           m_zoomf = 16.f;
    int             m_zoomLevel = 16;
};
