#include "PlayerComponent.h"
#include "Engine.h"
#include "Math/Vector2.h"
#include <iostream>

namespace wrap
{
	void wrap::PlayerComponent::Update()
	{
		Vector2 direction = Vector2::zero;
		if (wrap::g_inputSystem.GetKeyState(wrap::key_left) == wrap::InputSystem::KeyState::Held
			|| wrap::g_inputSystem.GetKeyState(wrap::key_a) == wrap::InputSystem::KeyState::Held
			)
		{
			m_owner->m_transform.rotation -= 200 * g_time.deltaTime;
			//std::cout << "left\n";
		}
		
		if (wrap::g_inputSystem.GetKeyState(wrap::key_right) == wrap::InputSystem::KeyState::Held
			|| wrap::g_inputSystem.GetKeyState(wrap::key_d) == wrap::InputSystem::KeyState::Held
			)
		{
			m_owner->m_transform.rotation += 200 * g_time.deltaTime;
			//std::cout << "right\n";
		}

		float thrust = 50;
		if (wrap::g_inputSystem.GetKeyState(wrap::key_up) == wrap::InputSystem::KeyState::Held
			|| wrap::g_inputSystem.GetKeyState(wrap::key_w) == wrap::InputSystem::KeyState::Held
			)
		{
			thrust = speed;
			//std::cout << "up\n";
		}

		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			//thrust force
			Vector2 force = Vector2::Rotate({ 1, 0 }, math::DegToRad(m_owner->m_transform.rotation)) * thrust;
			component->ApplyForce(force);

			//grav force
			//force = (Vector2{ 400,300 } - m_owner->m_transform.position).Normalized() * 50.0f;
			//component->ApplyForce(force);
		}

		//m_owner->m_transform += direction * 300 * g_time.deltaTime;

		if (g_inputSystem.GetKeyState(key_space) == InputSystem::KeyState::Pressed)
		{
			auto component = m_owner->GetComponent<AudioComponent>();
			if (component)
			{
				component->Play();
			}
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

}
