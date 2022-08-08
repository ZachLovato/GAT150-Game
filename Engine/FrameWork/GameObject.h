#pragma once
#include "../Math/Transform.h"

namespace wrap
{
	class GameObjects
	{
	public:
		GameObjects() = default;
		
		virtual void Update() = 0;
		
		Transform m_transform;
	};
}