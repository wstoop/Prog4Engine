#include "FPSComponent.h"
#include "TimeManager.h"
#include "GameObject.h"
#include "TextComponent.h"
#include <format>
namespace dae
{
    constexpr float FPS_UPDATE_INTERVAL = 0.30f;

    FPSComponent::FPSComponent()
        : m_FPS(0.0f), m_FrameCount(0), m_ElapsedTime(0.0f)
    {
    }

    void FPSComponent::Update()
    {
        CalculateFPS();
    }

    void FPSComponent::FixedUpdate(float fixedTimeStep)
    {
        (void)fixedTimeStep;
    }

    void FPSComponent::LateUpdate()
    {
        m_owner->GetComponent<TextComponent>()->SetText("FPS: " + std::format("{:.1f}", m_FPS));
    }

    void FPSComponent::CalculateFPS()
    {
        auto& timeManager = TimeManager::GetInstance();
        CalculateFPS(timeManager.GetDeltaTime());
    }

    void FPSComponent::CalculateFPS(float deltaTime)
    {
        m_ElapsedTime += deltaTime;
        ++m_FrameCount;
        if (m_ElapsedTime >= FPS_UPDATE_INTERVAL)
        {
            m_FPS = static_cast<float>(m_FrameCount) / m_ElapsedTime;
            m_FrameCount = 0;
            m_ElapsedTime = 0.0f;
        }
    }

    float FPSComponent::GetFPS() const
    {
        return m_FPS;
    }
}