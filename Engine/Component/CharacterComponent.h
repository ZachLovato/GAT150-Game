#pragma once
#include "Framework/Component.h"
#include "Physics/Collission.h"
#include "Framework/Event.h"

namespace wrap
{
	class CharacterComponent : public Component, public ICollision, public INotify
	{
	public:
		CharacterComponent() = default;
		virtual ~CharacterComponent();
	
		virtual void Initialize() override;
		virtual bool Write(const rapidjson::Value& value) const override;
		
		virtual bool Read(const rapidjson::Value& value) override;
		
		virtual std::unique_ptr<GameObject> Clone() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Actor* other) override;
		virtual void OnCollisionExit(Actor* other) override;

		virtual void OnNotify(const Event& event) override;
	
	public:
 		float health = 100;
		float damage = 10;
		float speed = 0;

	};
}