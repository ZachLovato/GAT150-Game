#pragma once
#include "../Math/Transform.h"

#define REGISTER_CLASS(class) Factory::Instance().Register<class>(#class)

namespace wrap
{
	class GameObject
	{
	public:
		GameObject() = default;
		
		virtual void Update() = 0;
		
		Transform m_transform;
	};
}