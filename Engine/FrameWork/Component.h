#pragma once
#include "GameObject.h"

namespace wrap
{
	class Actor;

	class Component : public GameObjects
	{
	public:
		Component() = default;

		virtual void Update() = 0;

		friend class Actor;
	protected:
		Actor* m_owner = nullptr;
	};
}