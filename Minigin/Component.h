#pragma once
class GameObject;
namespace dae
{
	class Component
	{
		GameObject* m_pOwner;
	public:
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
		virtual void Render() const {};
		virtual void Update() = 0;
		virtual void LateUpdate() {};
		virtual void FixedUpdate() {};
	protected:
		explicit Component(GameObject* pOwner) : m_pOwner(pOwner) {}
		GameObject* GetOwner() const { return m_pOwner; }
	};
}


