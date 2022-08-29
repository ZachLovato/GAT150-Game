#pragma once

#include"Serialization/Json.h"

#include "Core/file.h"
#include "Core/Memory.h"
#include "Core/Time.h"
#include "Core/Logger.h"

#include "Math/MathUtils.h"
#include "Math/Random.h"

#include "FrameWork/Scene.h"
#include "FrameWork/Game.h"
#include "FrameWork/Factory.h"
#include "FrameWork/SimpleTon.h"

#include "Component/PlayerComponent.h"
#include "Component/CollisionComponent.h"
#include "Component/SpriteComponent.h"
#include "Component/SpriteAniComponent.h"
#include "Component/AudioComponent.h"
#include "Component/PhysicsComponent.h"
#include "Component/RBPhysicsComponent.h"
#include "Component/ModelComponent.h"
#include "Component/TextComponent.h"
#include "Component/TilemapComponent.h"

#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Resource/ResourceManager.h"

#include "Renderer/Renderer.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/Texture.h"
#include "Renderer/Model.h"

#include "Physics/PhysicsSystem.h"

#include <memory>
#include <list>
#include <vector>

namespace wrap
{
	extern InputSystem g_inputSystem;
	extern Renderer g_renderer;
	extern Time g_time;
	extern AudioSystem g_audio;
	extern ResourceManager g_resources;
	extern PhysicsSystem g_physicsSystem;

	class Engine : public Singleton<Engine>
	{
	public:
		void Register();
	};

}