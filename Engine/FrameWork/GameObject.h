#pragma once
#include "../Math/Transform.h"
#include "Serialization/Serializable.h"

#define REGISTER_CLASS(class) Factory::Instance().Register<class>(#class)

namespace wrap
{
	class GameObject
	{
	public:
		GameObject() = default;
		
		virtual void Initialize() {};
		virtual void Update() = 0;

		
		Transform m_transform;
	};
}