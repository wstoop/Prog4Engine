#pragma once
#include "Singleton.h"

namespace dae
{
    class TimeManager final : public Singleton<TimeManager>
    {
    public:
        float m_DeltaTime{};
        float m_FixedTimeStep{ 1.0f / 60.0f };
    private:
        TimeManager() = default;
        friend Singleton<TimeManager>;
    };
}
