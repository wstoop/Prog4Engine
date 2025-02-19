#pragma once
#include "Renderer.h"
#include <string>
#include <memory>
#include "Component.h"

class Texture2D;
namespace dae
{
	class SpriteSheetComponent final : public Component
	{
	public:
		SpriteSheetComponent(GameObject* pOwner, const std::string& spritesheet, float frameTime, int numRows, int numColumns);

		// Correctly override the virtual functions from Component
		void Render() const override;
		void Update() override;

		// Spritesheet-specific functionality
		void NewAnimation(int numFrames, int beginFrame, int beginRow, float frameTime, bool loop);

		~SpriteSheetComponent() override = default;
		SpriteSheetComponent(const SpriteSheetComponent&) = delete;
		SpriteSheetComponent& operator=(const SpriteSheetComponent&) = delete;
		SpriteSheetComponent(SpriteSheetComponent&&) = delete;
		SpriteSheetComponent& operator=(SpriteSheetComponent&&) = delete;
	private:
		void SetTexture(const std::string& spritesheet);
		
		// Spritesheet texture
		std::shared_ptr<Texture2D> m_pSpritesheet;

		// Sprite layout
		const int m_NumRows;
		const int m_NumColumns;
		float m_SpriteWidth;
		float m_SpriteHeight;

		// Animation properties
		int m_NumFrames;
		int m_CurrFrame;
		int m_BeginFrame; // First frame (horizontal position)
		int m_BeginRow;   // First row (1 = top)
		bool m_IsLooping;

		// Timing
		float m_FrameTime;
		float m_AccumulatedTime;

		mutable bool m_NeedsUpdate{ true };
		mutable SDL_Rect m_cachedSrcRect{};
	};
}