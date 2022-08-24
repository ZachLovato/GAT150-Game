#include "PhysicsComponent.h"
#include "Engine.h"

namespace wrap
{
	void wrap::PhysicsComponent::Update()
	{
		velocity += acceleration * g_time.deltaTime;
		m_owner->m_transform.position += velocity * g_time.deltaTime;
		velocity *= damping;

		acceleration = Vector2::zero;
	}

	void PhysicsComponent::Initilize()
	{
	}

	bool PhysicsComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool PhysicsComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, damping);
		//READ_DATA(value, velocity);
		//READ_DATA(value, acceleration);

		return true;
	}

}

