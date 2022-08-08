#include "Engine.h"
#include <iostream>


int main() {

	
	wrap::InitializeMemory();
	wrap::g_inputSystem.Initialize();
	wrap::g_renderer.Initailized();
	wrap::g_audio.Initialize();

	wrap::SetFilePath("../Assets");

	//create window
	wrap::g_renderer.CreateWindow("Game", 800, 600);
	wrap::g_renderer.SetClearColor(wrap::Color{ 0,0,0,0 });
		
	//resources
	std::shared_ptr<wrap::Texture> texture = std::make_shared<wrap::Texture>();
	texture->Create(wrap::g_renderer, "Sprites/Orber.png");

	wrap::g_audio.AddAudio("bg", "rocket.wav");

	//create Actors
	wrap::Scene scene;
	
	wrap::Transform transform{ { 400, 300}, 90, { 0 , 0 } };
	std::unique_ptr<wrap::Actor> actor = std::make_unique<wrap::Actor>();
	std::unique_ptr<wrap::PlayerComponent> pcomponent = std::make_unique<wrap::PlayerComponent>();
	actor->AddComponent(std::move(pcomponent));

	std::unique_ptr<wrap::SpriteComponent> sprcomponent = std::make_unique<wrap::SpriteComponent>();
	sprcomponent->m_texture = texture;
	actor->AddComponent(std::move(sprcomponent));

	std::unique_ptr<wrap::AudioComponent> acomponent = std::make_unique<wrap::AudioComponent>();
	acomponent->m_soundName = "bg";
	actor->AddComponent(std::move(acomponent));

	std::unique_ptr<wrap::PhysicsComponent> phcomponent = std::make_unique<wrap::PhysicsComponent>();
	actor->AddComponent(std::move(phcomponent));

	scene.Add(std::move(actor));

	float angle = 0;

	bool quit = false;
	while (!quit)
	{
		// update (engine)
		wrap::g_time.Tick();
		wrap::g_inputSystem.Update();
		wrap::g_audio.Update();

		if (wrap::g_inputSystem.GetKeyState(wrap::key_escape) == wrap::InputSystem::KeyState::Pressed) quit = true;
		
		//update Scene
		angle += 10.0f * wrap::g_time.deltaTime;
		scene.Update();

		wrap::g_renderer.BeginFrame();

		scene.Draw(wrap::g_renderer);
		//wrap::g_renderer.Draw(texture, { 400, 300 }, angle, { 5.0f , 5.0f }, { .5f ,1.0f });//.5 1

		wrap::g_renderer.EndFrame();
	}

	wrap::g_renderer.Shutdown();
	wrap::g_audio.Shutdown();
}