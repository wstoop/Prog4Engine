#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h" 

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
    std::for_each(m_components.begin(), m_components.end(), [](const auto& component) {
        component->Update();
    });
}

void dae::GameObject::LateUpdate()
{
    std::for_each(m_components.begin(), m_components.end(), [](const auto& component) {
        component->LateUpdate();
        });
}

void dae::GameObject::FixedUpdate(float fixedTimeStep)
{
    std::for_each(m_components.begin(), m_components.end(), [fixedTimeStep](const auto& component) {
        component->FixedUpdate(fixedTimeStep);
        });
}

void dae::GameObject::Render() const
{
    std::for_each(m_components.begin(), m_components.end(), [](const auto& component) {
        component->Render();
        });
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
