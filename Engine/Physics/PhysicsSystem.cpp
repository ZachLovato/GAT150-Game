#include "PhysicsSystem.h" 

namespace wrap
{
	void PhysicsSystem::Initialize()
	{
		b2Vec2 gravity{ 0, 10 };
		world = std::make_unique<b2World>(gravity);
	}

	void PhysicsSystem::Shutdown()
	{
	}

	void PhysicsSystem::Update()
	{
	}
}