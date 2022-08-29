#pragma once
//#include "../Math/Transform.h" //where do i move this too
#include "Serialization/Serializable.h"

#define CLASS_DECLARATION(class) \
	std::unique_ptr<GameObject> Clone() override { return std::make_unique<class>(*this); }
#define REGISTER_CLASS(class) Factory::Instance().Register<class>(#class)

namespace wrap
{
	class GameObject
	{
	public:
		GameObject() = default;
		
		virtual std::unique_ptr<GameObject> Clone() = 0;
		virtual void Initialize() {};
		virtual void Update() = 0;


		
		//Transform m_transform; // and this 
	};
}