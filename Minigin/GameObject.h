#pragma once
#include <memory>
#include <vector>
#include "Transform.h"

namespace dae
{
	class Texture2D;
	class Component;

	class GameObject final
	{
	public:
		void Update();
		void LateUpdate();
		void FixedUpdate(float fixedTimeStep);
		void Render() const;

		void SetPosition(float x, float y);

		template <typename T>
		std::shared_ptr<T> GetComponent() const
		{
			for (const auto& component : m_components)
			{
				if (auto castedComponent = std::dynamic_pointer_cast<T>(component))
				{
					return castedComponent;
				}
			}
			return nullptr;
		}

		template <typename T, typename... Args>
		std::shared_ptr<T> AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
			auto component = std::make_shared<T>(std::forward<Args>(args)...);
			component->SetOwner(this);
			m_components.push_back(component);
			return component;
		}

		template <typename T>
		void RemoveComponent()
		{
			m_components.erase(
				std::remove_if(m_components.begin(), m_components.end(),
					[](const std::shared_ptr<Component>& component)
					{
						return std::dynamic_pointer_cast<T>(component) != nullptr;
					}),
				m_components.end());
		}

		Transform GetTransform() const { return m_transform; }
		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_transform{};
		std::vector<std::shared_ptr<Component>> m_components{};
	};
}
