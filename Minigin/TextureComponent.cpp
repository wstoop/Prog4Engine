#include "Renderer.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextureComponent.h"

namespace dae
{
    TextureComponent::TextureComponent(GameObject* owner, const std::string& filename):
		Component(owner)
    {
        SetTexture(filename);
    }

    void TextureComponent::Render() const
    {
        if (m_texture)
        {
			const auto pos = Component::GetOwner()->GetTransform().GetPosition();
            Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
        }
    }

    void TextureComponent::SetTexture(const std::string& filename)
    {
        m_texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
    }

	void TextureComponent::Update()
	{

	}
}
