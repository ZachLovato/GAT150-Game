#include "Engine.h"

namespace wrap
{
	InputSystem g_inputSystem;
	Renderer g_renderer;
	Time g_time;
	AudioSystem g_audio;
	ResourceManager g_resources;
	PhysicsSystem g_physicsSystem;

	void Engine::Register()
	{
		REGISTER_CLASS(Actor);
		REGISTER_CLASS(CollisionComponent);
		REGISTER_CLASS(AudioComponent);
		REGISTER_CLASS(ModelComponent);
		REGISTER_CLASS(PhysicsComponent);
		REGISTER_CLASS(RBPhysicsComponent);
		REGISTER_CLASS(PlayerComponent);
		REGISTER_CLASS(SpriteComponent);
		REGISTER_CLASS(SpriteAniComponent);
		REGISTER_CLASS(TextComponent);
		REGISTER_CLASS(TilemapComponent);
	}

}