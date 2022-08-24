#pragma once
#include "FrameWork/Component.h"
#include "Physics/Collission.h"
#include "Physics/PhysicsSystem.h"

namespace wrap
{
	class CollisionComponent : public Component, public ICollision
	{
		
		virtual void Initialize() override;
		virtual void Update() override;
		
		virtual void OnCollisionEnter(Actor* other) override;
		virtual void OnCollisionExit(Actor* other) override;
		
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	private:
		PhysicsSystem::CollisionData data;

	};
}