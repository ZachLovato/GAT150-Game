#pragma once
#include "FrameWork/Component.h"
#include "CharacterComponent.h"

namespace wrap
{
	class PlayerComponent : public CharacterComponent
	{
	public:
		PlayerComponent() = default;

		CLASS_DECLARATION(PlayerComponent)


		void Initalize();
		void Update() override;
		
		virtual void OnNotify(const Event& event) override;
		virtual void OnCollisionEnter(Actor* other) override;
		virtual void OnCollisionExit(Actor* other) override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
	

		float jump = 30.0f;

	};
}