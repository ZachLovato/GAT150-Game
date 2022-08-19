#include "Engine.h"
#include <iostream>

int main() {
	
	wrap::InitializeMemory();
	wrap::g_inputSystem.Initialize();
	wrap::g_renderer.Initailized();
	wrap::g_audio.Initialize();
	wrap::g_resources.Initialize();

	wrap::Engine::Instance().Register();

	wrap::SetFilePath("../Assets");

	//create window
	wrap::g_renderer.CreateWindow("Game", 800, 600);
	wrap::g_renderer.SetClearColor(wrap::Color{ 0 , 0 , 0 , 0 });

	//create Scene
	wrap::Scene scene;
	
	rapidjson::Document document;
	bool success = wrap::json::Load("level.txt", document);
	//assert(success);

	scene.Read(document);

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
		scene.Update();

		wrap::g_renderer.BeginFrame();

		scene.Draw(wrap::g_renderer);

		wrap::g_renderer.EndFrame();
	}

	wrap::g_renderer.Shutdown();
	wrap::g_audio.Shutdown();
}