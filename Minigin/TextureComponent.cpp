#include "TextureComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ResourceManager.h"

namespace dae
{
    TextureComponent::TextureComponent(const std::string& filename)
    {
        SetTexture(filename);
    }

    void TextureComponent::Render() const
    {
        if (m_texture)
        {
			const auto pos = m_owner->GetTransform().GetPosition();
            Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
        }
    }

    void TextureComponent::SetTexture(const std::string& filename)
    {
        m_texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
    }
}
