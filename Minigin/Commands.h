#pragma once
#include "MoveComponent.h"
#include "GameObject.h"

namespace dae
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};


    class GameObject;
    class GameObjectCommand : public Command
    {
        GameObject* m_pOwner;
    public:
        GameObjectCommand(GameObject* pOwner)
            : m_pOwner{ pOwner }
        {

        }

        virtual ~GameObjectCommand() override = default;

        GameObjectCommand(const GameObjectCommand& other) = delete;
        GameObjectCommand(GameObjectCommand&& other) noexcept = delete;
        GameObjectCommand& operator=(const GameObjectCommand& other) = delete;
        GameObjectCommand& operator=(GameObjectCommand&& other)	noexcept = delete;
    protected:
        GameObject* GetOwner() const { return m_pOwner; }
    };


	class MoveCommand : public GameObjectCommand
	{
        glm::vec3 m_MoveDir{ 0, 0, 0 };
	public:
        MoveCommand(GameObject* owner, glm::vec3 dir) :
            GameObjectCommand(owner),
            m_MoveDir(dir)
        {

        }
        virtual void Execute() override;
	};
}


