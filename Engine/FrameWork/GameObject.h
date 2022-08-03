#pragma once
#include "../Math/Transform.h"

namespace wrap
{
	class GameObjects
	{
	public:
		GameObjects() = default;
		GameObjects(const Transform& transform) : m_transform{ transform } {}

		virtual void Update() = 0;
		
	
		Transform m_transform;
	protected:

	};
}