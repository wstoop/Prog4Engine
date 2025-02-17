#pragma once
#include "Component.h"
#include "Texture2D.h"
#include <string>
#include <memory>

namespace dae
{
    class TextureComponent final : public Component
    {
    public:
        TextureComponent(GameObject* owner, const std::string& filename);
        ~TextureComponent() override = default;

        void Render() const override;
		void Update() override;
        void SetTexture(const std::string& filename);

    private: 
		friend class Component;
        std::shared_ptr<Texture2D> m_texture;
    };
}
