#include "PlayerComponent.h"
#include "Engine.h"
#include "Math/Vector2.h"
#include <iostream>

namespace wrap
{
	void PlayerComponent::Initalize()
	{
		CharacterComponent::Initialize();
	}

	void wrap::PlayerComponent::Update()
	{
		// set camera 
		auto camera = m_owner->GetScene()->GetActorFromName("Camera");
		if (camera)
		{
			camera->m_transform.position = math::Lerp(camera -> m_transform.position, m_owner->m_transform.position, 2 * g_time.deltaTime);
		}

		Vector2 direction = Vector2::zero;

		if (wrap::g_inputSystem.GetKeyState(wrap::key_left) == wrap::InputSystem::KeyState::Held
			|| wrap::g_inputSystem.GetKeyState(wrap::key_a) == wrap::InputSystem::KeyState::Held
			)
		{
			direction = Vector2::left;
		}
		
		if (wrap::g_inputSystem.GetKeyState(wrap::key_right) == wrap::InputSystem::KeyState::Held
			|| wrap::g_inputSystem.GetKeyState(wrap::key_d) == wrap::InputSystem::KeyState::Held
			)
		{
			direction = Vector2::right;
		}

		if (onGround && 
			wrap::g_inputSystem.GetKeyState(wrap::key_up) == wrap::InputSystem::KeyState::Pressed
			|| wrap::g_inputSystem.GetKeyState(wrap::key_w) == wrap::InputSystem::KeyState::Pressed
			)
		{
			auto component = m_owner->GetComponent<PhysicsComponent>(); // jump
			if (component)
			{
				component->ApplyForce(Vector2::up * jump);
			}

		}

		Vector2 velocity;
		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			// if in the air (m_groundCount == 0) then reduce force 
			std::cout << onGround << std::endl;
			float multiplier = (onGround) ? 1 : 0.2f;

			component->ApplyForce(direction * 20 * multiplier);
			velocity = component->velocity;
			//component->ApplyForce(direction * 20);
			//velocity = component->velocity;
		}


		if (g_inputSystem.GetKeyState(key_space) == InputSystem::KeyState::Pressed)
		{
			auto component = m_owner->GetComponent<PhysicsComponent>();
			if (component)
			{
				component->ApplyForce(Vector2::up * 250);
			}
		}

		auto aniComponent = m_owner->GetComponent<SpriteAniComponent>();
		if (aniComponent)
		{
			if (velocity.x != 0) aniComponent->GetFlipHorizontal(velocity.x < 0);
			if (std::fabs(velocity.x) > 0)
			{
				aniComponent->SetSequence("run");
			}
			else
			{
				aniComponent->SetSequence("idle");
			}
		}

	}

	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		CharacterComponent::Read(value);
		READ_DATA(value, jump);


		return true;
	}

	void PlayerComponent::OnNotify(const Event& event)
	{
		if (event.name == "EVENT_DAMAGE")
		{
			std::cout << health << std::endl;
			health -= std::get<float>(event.data);
			if (health <= 0)
			{
				m_owner->SetDestory();

				Event event;

				event.name = "EVENT_PLAYER_DEAD";

				g_eventManager.Notify(event);
			}
		}
	}

	void PlayerComponent::OnCollisionEnter(Actor* other)
	{
		if (other->GetTag() == "Ground")
		{
			m_groundCount++;
		}

		if (other->GetName() == "Oil")
		{
			Event event;
			event.name = "EVENT_ADD_POINTS";
			event.data = 100;
			g_eventManager.Notify(event);
			other->SetDestory();
		}

		if (other->GetTag() == "Enemy")
		{
			Event event;
			event.name = "EVENT_DAMAGE";
			event.data = damage;
			event.receiver = other;

			g_eventManager.Notify(event);
		}
	}

	void PlayerComponent::OnCollisionExit(Actor* other) // the collsion for enter goes here
	{
		if (other->GetTag() == "Pickup")
		{
			Event event;
			event.name = "EVENT_ADD_POINTS";
			event.data = 100;
			g_eventManager.Notify(event);
			other->SetDestory();
		}

		if (other->GetTag() == "Enemy")
		{
			Event event;
			event.name = "EVENT_DAMAGE";
			event.data = damage;
			event.receiver = other;

			g_eventManager.Notify(event);
		}
	}

}
