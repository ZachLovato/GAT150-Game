#pragma once
#include "FrameWork/Component.h"
#include "Physics/Collission.h"
#include "Physics/PhysicsSystem.h"
#include <functional>

namespace wrap
{
	class CollisionComponent : public Component, public ICollision
	{
	public:
		using FunctionPtr = std::function<void(Actor*)>;


		virtual void Initialize() override;
		virtual void Update() override;
		
		virtual void OnCollisionEnter(Actor* other) override;
		virtual void OnCollisionExit(Actor* other) override;

		void SetCollisionEnter(FunctionPtr function) { m_enterFunction = function; }
		void SetCollisionExit(FunctionPtr function) { m_enterFunction = function; }
		
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	private:
		PhysicsSystem::CollisionData data;

		FunctionPtr m_enterFunction;
		FunctionPtr m_exitFunction;

	};
}