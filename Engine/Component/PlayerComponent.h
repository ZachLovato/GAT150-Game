#pragma once
#include "FrameWork/Component.h"

namespace wrap
{
	class PlayerComponent : public Component
	{
	public:
		PlayerComponent() = default;

		void Update() override;

	private:
		float m_speed = 200.0f;

	};
}