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
        TextureComponent(const std::string& filename);
        ~TextureComponent() override = default;

        void Update() override {}
        void LateUpdate() override {}
        void FixedUpdate(float) override {}
        void Render() const override;

        void SetTexture(const std::string& filename);

    private: 
		friend class Component;
        std::shared_ptr<Texture2D> m_texture;
    };
}
