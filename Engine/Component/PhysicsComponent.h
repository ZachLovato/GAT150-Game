#pragma once
#include "FrameWork/Component.h"
#include "Math/Vector2.h"

namespace wrap
{
	class  PhysicsComponent: public Component
	{
	public:
		PhysicsComponent () = default;

		void Update() override;
		void ApplyForce(const Vector2& force) { acceleration += force; }

		// Inherited via Component
		virtual bool Write(const rapidjson::Value& value) const override;

		virtual bool Read(const rapidjson::Value& value) override;
	private:
		Vector2 velocity;
		Vector2 acceleration;

		float damping = 0;



	};
}
