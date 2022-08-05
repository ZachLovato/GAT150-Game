#pragma once
#include "FrameWork/Component.h"

namespace wrap
{
	class PlayerComponent : public Component
	{
	public:
		PlayerComponent() = default;

		void Update() override;



	};
}