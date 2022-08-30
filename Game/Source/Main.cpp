#include "Engine.h"
#include "MyGame.h"
#include <iostream>

int main() {
	
	wrap::InitializeMemory();
	wrap::g_inputSystem.Initialize();
	wrap::g_renderer.Initailized();
	wrap::g_audio.Initialize();
	wrap::g_resources.Initialize();
	wrap::g_physicsSystem.Initialize();
	wrap::g_eventManager.Initialize();

	wrap::Engine::Instance().Register();

	wrap::SetFilePath("../Assets");

	//create window
	wrap::g_renderer.CreateWindow("Game", 800, 600);
	wrap::g_renderer.SetClearColor(wrap::Color{ 0 , 0 , 0 , 0 });

	//create Scene
	std::unique_ptr<MyGame> game = std::make_unique<MyGame>();

	game->Initialize();

	float angle = 0;

	bool quit = false;
	while (!quit)
	{
		// update (engine)
		wrap::g_time.Tick();
		wrap::g_inputSystem.Update();
		wrap::g_physicsSystem.Update();
		wrap::g_audio.Update();
		wrap::g_eventManager.Update();

		if (wrap::g_inputSystem.GetKeyState(wrap::key_escape) == wrap::InputSystem::KeyState::Pressed) quit = true;
		
		//update Scene
		game->Update();

		wrap::g_renderer.BeginFrame();

		game->Draw(wrap::g_renderer);

		wrap::g_renderer.EndFrame();
	}

	game->Shutdown();
	game.reset();

	wrap::Factory::Instance().Shutdown();

	wrap::g_audio.Shutdown();
	wrap::g_inputSystem.Shutdown();
	wrap::g_physicsSystem.Shutdown();
	wrap::g_renderer.Shutdown();
	wrap::g_audio.Shutdown();
}