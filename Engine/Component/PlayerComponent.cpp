#include "PlayerComponent.h"
#include "Engine.h"
#include "Math/Vector2.h"
#include <iostream>

namespace wrap
{
	void PlayerComponent::Initalize()
	{
		auto component = m_owner->GetComponent<CollisionComponent>();
		if (component)
		{
			component->SetCollisionEnter(std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1));
			component->SetCollisionExit(std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1));
		}
	}

	void wrap::PlayerComponent::Update()
	{
		Vector2 direction = Vector2::zero;

		if (wrap::g_inputSystem.GetKeyState(wrap::key_left) == wrap::InputSystem::KeyState::Held
			|| wrap::g_inputSystem.GetKeyState(wrap::key_a) == wrap::InputSystem::KeyState::Held
			)
		{
			direction = Vector2::left;
			//std::cout << "left\n";
		}
		
		if (wrap::g_inputSystem.GetKeyState(wrap::key_right) == wrap::InputSystem::KeyState::Held
			|| wrap::g_inputSystem.GetKeyState(wrap::key_d) == wrap::InputSystem::KeyState::Held
			)
		{
			direction = Vector2::right;
			//std::cout << "right\n";
		}

		//float thrust = 0;
		if (wrap::g_inputSystem.GetKeyState(wrap::key_up) == wrap::InputSystem::KeyState::Pressed
			|| wrap::g_inputSystem.GetKeyState(wrap::key_w) == wrap::InputSystem::KeyState::Pressed
			)
		{
			auto component = m_owner->GetComponent<PhysicsComponent>(); // jump
			if (component)
			{
				component->ApplyForce(Vector2::up * 600);
			}

			//thrust = speed;
			//std::cout << "up\n";
		}

		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			//thrust force
			//Vector2 force = Vector2::Rotate({ 1, 0 }, math::DegToRad(m_owner->m_transform.rotation)) * thrust;
			component->ApplyForce(direction * speed);

			//grav force
			//force = (Vector2{ 400,300 } - m_owner->m_transform.position).Normalized() * 50.0f;
			//component->ApplyForce(force);
		}

		//m_owner->m_transform += direction * 300 * g_time.deltaTime;

		if (g_inputSystem.GetKeyState(key_space) == InputSystem::KeyState::Pressed)
		{
			auto component = m_owner->GetComponent<PhysicsComponent>();
			if (component)
			{
				component->ApplyForce(Vector2::up * 30);
			}

			/*auto component = m_owner->GetComponent<AudioComponent>();
			if (component)
			{
				component->Play();
			}*/
		}

	}

	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, speed);


		return true;
	}

	void PlayerComponent::OnCollisionEnter(Actor* other)
	{
		std::cout << "player enter\n";

		if (other->GetName() == "Oil")
		{
			Event event;
			event.name = "EVENT ADD POINTS";
			event.data = 100;
			g_eventManager.Notify(event);
			other->SetDestory();
		}
		std::cout << "player enter\n";
	}

	void PlayerComponent::OnCollisionExit(Actor* other)
	{
		std::cout << "player exit\n";
	}

}
