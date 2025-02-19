#include "Texture2D.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "SpriteSheetComponent.h"

namespace dae
{
    SpriteSheetComponent::SpriteSheetComponent(GameObject* pOwner, const std::string& spritesheet, float frameTime, int numRows, int numColumns)
        : Component(pOwner)
        , m_NumRows(numRows)
        , m_NumColumns(numColumns)
        , m_NumFrames(1)
        , m_CurrFrame(1)
        , m_BeginFrame(1)
        , m_BeginRow(1)
        , m_FrameTime(frameTime)
        , m_AccumulatedTime(0.f)
        , m_IsLooping(true)
        , m_NeedsUpdate(true)   // Mark as dirty initially
    {
        SetTexture(spritesheet);

        // Calculate individual sprite dimensions based on texture size and layout
        m_SpriteWidth = static_cast<float>(m_pSpritesheet->GetSize().x / m_NumColumns);
        m_SpriteHeight = static_cast<float>(m_pSpritesheet->GetSize().y / m_NumRows);
    }

    void SpriteSheetComponent::Render() const
    {
        // If our cached source rectangle is dirty, recalculate it.
        if (m_NeedsUpdate)
        {
            if (m_NumFrames == 1)
            {
                m_cachedSrcRect.x = static_cast<int>(m_SpriteWidth * (m_BeginFrame - 1));
                m_cachedSrcRect.y = static_cast<int>(m_SpriteHeight * m_BeginRow);
                m_cachedSrcRect.w = static_cast<int>(m_SpriteWidth);
                m_cachedSrcRect.h = static_cast<int>(m_SpriteHeight);
            }
            else
            {
                const int frameIndex = m_BeginFrame + m_CurrFrame - 2;
                m_cachedSrcRect.x = static_cast<int>(m_SpriteWidth * (frameIndex % m_NumColumns));
                m_cachedSrcRect.y = static_cast<int>(m_SpriteHeight * (m_BeginRow + (frameIndex / m_NumColumns)));
                m_cachedSrcRect.w = static_cast<int>(m_SpriteWidth);
                m_cachedSrcRect.h = static_cast<int>(m_SpriteHeight);
            }
            m_NeedsUpdate = false;
        }

        // Get the world position from the owner object
        const auto pos = GetOwner()->GetWorldPosition();

        // Render the texture using the renderer, passing the cached source rectangle ("box")
        Renderer::GetInstance().RenderTexture(*m_pSpritesheet, pos.x, pos.y, m_SpriteWidth * 3, m_SpriteHeight * 3, &m_cachedSrcRect);
    }

    void SpriteSheetComponent::Update()
    {

        // Accumulate elapsed time and update the current frame if enough time has passed
        m_AccumulatedTime += TimeManager::GetInstance().GetDeltaTime();
        if (m_AccumulatedTime >= m_FrameTime)
        {
            if (m_IsLooping || (!m_IsLooping && m_CurrFrame < m_NumFrames))
            {
                ++m_CurrFrame;
                if (m_CurrFrame > m_NumFrames)
                    m_CurrFrame = 1;  // Loop back to the first frame

                m_AccumulatedTime = 0.f;
                m_NeedsUpdate = true; // Mark source rectangle as dirty since frame changed
            }
        }
    }

    void SpriteSheetComponent::NewAnimation(int numFrames, int beginFrame, int beginRow, float frameTime, bool loop)
    {
        m_NumFrames = numFrames;
        m_BeginFrame = beginFrame;
        m_BeginRow = beginRow;
        m_IsLooping = loop;
        m_CurrFrame = 1;         // Reset animation to first frame
        m_AccumulatedTime = 0.f; // Reset accumulated time
        m_NeedsUpdate = true;    // Mark as dirty so source rect recalculates
		m_FrameTime = frameTime;
    }

	void SpriteSheetComponent::SetTexture(const std::string& spritesheet)
	{
		m_pSpritesheet = ResourceManager::GetInstance().LoadTexture(spritesheet);
	}
}