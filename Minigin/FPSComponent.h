#pragma once
#include <string>
#include <memory>
#include "Component.h"

namespace dae
{
	class FPSComponent final : public Component
	{
	public:
		FPSComponent();
		~FPSComponent() override = default;
		void Update() override;
		void LateUpdate() override;
		void FixedUpdate(float fixedTimeStep) override;

		void CalculateFPS();
		void CalculateFPS(float deltaTime);
		float GetFPS() const;

	private:
		friend class Component;
		float m_FPS{ 0.0f };
		int m_FrameCount{ 0 };
		float m_ElapsedTime{ 0.0f };
		
	};
}