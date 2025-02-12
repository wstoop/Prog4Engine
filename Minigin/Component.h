#pragma once

namespace dae
{
    class GameObject;

    class Component
    {
    public:
        virtual ~Component() = default;

        virtual void Update() = 0;
        virtual void LateUpdate() = 0;
        virtual void FixedUpdate(float fixedTimeStep) = 0;
        virtual void Render() const = 0;

        void SetOwner(GameObject* owner) { m_owner = owner; }
        GameObject* GetOwner() const { return m_owner; }

    protected:
        GameObject* m_owner{ nullptr };
    };
}
