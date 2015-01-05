#include "CircuitFx.h"

const float INCLINED_RATIO = GOLDEN_SECOND;
const float GRID_SIZE = 32.f;
const float GRID_SIZE_X = GRID_SIZE * INCLINED_RATIO * 2.f;
const float GRID_SIZE_Y = GRID_SIZE;
const float TRAIL_SPEED = 50.f;

extern OPal g_pal;

CircuitFx::CircuitFx(const Vector2& pos) :
    m_pos(pos),
    m_colorFrom(g_pal[0]),
    m_colorTo(Color::Transparent)
{
    m_circuitIncome.start(0.015f, 1.f);
    m_spawnTimer.start(m_circuitIncome.get(), std::bind(&CircuitFx::spawnTrail, this));
    m_colorFrom *= .25f;
}

void CircuitFx::update()
{
    for (decltype(m_trailPool.size()) i = 0; i < m_trailPool.size(); ++i)
    {
        auto pTrail = m_trailPool.at<sCircuitTrail>(i);
        if (m_trailPool.isUsed(pTrail))
        {
            // Slowly zoom in all points
            for (auto& point : pTrail->points)
            {
                auto pt = point - m_pos;
                float percent = pt.x / 2000.f + pt.y / 2000.f;
                pt += pt * ODT * percent;
                point = pt + m_pos;
            }

            if (pTrail->stopped)
            {
                pTrail->progress += ODT;
                if (pTrail->progress >= 1.f)
                {
                    m_trailPool.dealloc(pTrail);
                }
            }
            else
            {
                pTrail->progress += ODT * TRAIL_SPEED;
                if (pTrail->progress >= 1.f)
                {
                    pTrail->progress -= 1.f;
                    pTrail->activeCount++;
                    if (pTrail->activeCount > pTrail->count)
                    {
                        pTrail->activeCount = pTrail->count;
                        pTrail->stopped = true;
                    }
                }
            }
            for (decltype(pTrail->activeCount) index = 0; index < ((pTrail->stopped) ? (pTrail->activeCount) : (pTrail->activeCount - 1)); ++index)
            {
                auto& color = pTrail->colors[index];
                color -= ODT;
                if (color < 0.f) color = 0.f;
            }
        }
    }
}

void CircuitFx::render()
{
    for (decltype(m_trailPool.size()) i = 0; i < m_trailPool.size(); ++i)
    {
        auto pTrail = m_trailPool.at<sCircuitTrail>(i);
        if (m_trailPool.isUsed(pTrail))
        {
            OPB->begin(onut::ePrimitiveType::LINE_STRIP);
            for (decltype(pTrail->activeCount) index = 0; index < pTrail->activeCount - 1; ++index)
            {
                auto color = onut::lerp(m_colorTo, m_colorFrom, pTrail->colors[index]);
                OPB->draw(pTrail->points[index], color);
            }
            if (pTrail->stopped)
            {
                auto color = onut::lerp(m_colorTo, m_colorFrom, pTrail->colors[pTrail->activeCount - 1]);
                OPB->draw(pTrail->points[pTrail->activeCount - 1], color);
            }
            else
            {
                auto color = onut::lerp(m_colorTo, m_colorFrom, pTrail->colors[pTrail->activeCount - 1]);
                OPB->draw(onut::lerp(pTrail->points[pTrail->activeCount - 2], pTrail->points[pTrail->activeCount - 1], pTrail->progress), color);
            }
            OPB->end();

            if (!pTrail->stopped)
            {
                auto color = onut::lerp(m_colorTo, m_colorFrom, pTrail->colors[pTrail->activeCount - 1]);
                OSB->begin();
                OSB->drawSprite(OGetTexture("dot.png"), onut::lerp(pTrail->points[pTrail->activeCount - 2], pTrail->points[pTrail->activeCount - 1], pTrail->progress), color, 0.f, .35f);
                OSB->end();
            }
        }
    }
}

Vector2 CircuitFx::getDirForDir(int dir)
{
    switch (dir)
    {
        case 0:
        {
            return Vector2(GRID_SIZE_X, 0);
        }
        case 1:
        {
            return Vector2(GRID_SIZE_X * .5f, GRID_SIZE_Y);
        }
    /*    case 2:
        {
            return Vector2(0, GRID_SIZE_Y);
        }*/
        case 2:
        {
            return Vector2(-GRID_SIZE_X * .5f, GRID_SIZE_Y);
        }
        case 3:
        {
            return Vector2(-GRID_SIZE_X, 0);
        }
        case 4:
        {
            return Vector2(-GRID_SIZE_X * .5f, -GRID_SIZE_Y);
        }
     /*   case 6:
        {
            return Vector2(0, -GRID_SIZE_Y);
        }*/
        case 5:
        {
            return Vector2(GRID_SIZE_X * .5f, -GRID_SIZE_Y);
        }
    }
    return Vector2::Zero;
}

void CircuitFx::spawnTrail()
{
    auto pTrail = m_trailPool.alloc<sCircuitTrail>();
    if (pTrail)
    {
        pTrail->count = onut::randi(5, MAX_TRAIL_SIZE);

        // Define trail path
        auto rndX = onut::randi(-20, 20);
        auto rndY = onut::randi(-10, 10);
        pTrail->points[0] = {
            m_pos.x + static_cast<float>(rndX)* GRID_SIZE_X + static_cast<float>(rndY % 2) * GRID_SIZE_X * .5f,
            m_pos.y + static_cast<float>(rndY)* GRID_SIZE_Y
        };
        int lastRnd = 0;
        auto lastDir = onut::randi(0, 7);
        pTrail->points[1] = pTrail->points[0] + getDirForDir(lastDir);
        for (decltype(pTrail->count) i = 2; i < pTrail->count; ++i)
        {
            if (onut::randb(.25f))
            {
                lastDir = (lastDir + onut::randi(-1, 1)) % 6;
            }
            pTrail->points[i] = pTrail->points[i - 1] + getDirForDir(lastDir);
        }

        // Reset colors
        for (auto& color : pTrail->colors)
        {
            color = 1.f;
        }
    }

    // Spawn next trail
    m_spawnTimer.start(m_circuitIncome.get(), std::bind(&CircuitFx::spawnTrail, this));
}
