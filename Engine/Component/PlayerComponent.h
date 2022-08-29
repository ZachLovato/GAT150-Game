#pragma once
#include "FrameWork/Component.h"
#include "Physics/Collission.h"

namespace wrap
{
	class PlayerComponent : public Component, public ICollision
	{
	public:
		PlayerComponent() = default;

		CLASS_DECLARATION(PlayerComponent)


		void Initalize();
		void Update() override;
		
		virtual void OnCollisionEnter(Actor* other) override;
		virtual void OnCollisionExit(Actor* other) override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
	
		float speed = 0.0f;
	private:





	};
}