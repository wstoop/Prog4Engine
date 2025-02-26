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


		void SetParent(GameObject* parent, bool keepWorldPosition);
		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3& GetWorldPosition();
		void UpdateWorldPosition();
		GameObject* GetParent();

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
		bool IsChild(GameObject* child) const;
		void SetPositionDirty();
		glm::vec3 m_worldPosition{};
		glm::vec3 m_localPosition{};

		bool m_IsDestroyed = false;
		GameObject* m_parent = nullptr;
		bool m_positionIsDirty = true;
		std::vector<GameObject*> m_children{};
		std::vector<std::shared_ptr<Component>> m_components{};
	};
}
