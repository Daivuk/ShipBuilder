#pragma once
#include "onut.h"

class CircuitFx
{
public:
    CircuitFx(const Vector2& pos);

    void update();
    void render();

private:
    static const int    MAX_TRAIL_SIZE = 64;

    struct sCircuitTrail
    {
        Vector2     points[MAX_TRAIL_SIZE];
        float       colors[MAX_TRAIL_SIZE];
        int         count = MAX_TRAIL_SIZE;
        int         activeCount = 2;
        float       progress = 0.f;
        bool        stopped = false;
    };

    void            spawnTrail();
    static Vector2  getDirForDir(int dir);

    OTimer                                                              m_spawnTimer;
    Vector2                                                             m_pos;
    onut::Pool<sizeof(sCircuitTrail), 64U, sizeof(uintptr_t), false>    m_trailPool;
    Color                                                               m_colorFrom;
    Color                                                               m_colorTo;
    OAnimf                                                              m_circuitIncome = 1.f;
};
