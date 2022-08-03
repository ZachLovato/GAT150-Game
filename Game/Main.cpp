#include "Engine.h"
#include <iostream>

int main() {
	
	wrap::InitializeMemory();
	wrap::g_inputSystem.Initialize();
	wrap::g_renderer.Initailized();
	wrap::g_audio.Initialize();

	wrap::SetFilePath("../Assets");

	wrap::g_renderer.CreateWindow("Game", 800, 600);
	wrap::g_renderer.SetClearColor(wrap::Color{ 0,0,0,0 });

	
	std::shared_ptr<wrap::Texture> texture = std::make_shared<wrap::Texture>();
	texture->Create(wrap::g_renderer, "POWER.png");

	bool quit = false;
	while (!quit)
	{
		// update (engine)
		wrap::g_time.Tick();
		wrap::g_inputSystem.Update();
		wrap::g_audio.Update();

		if (wrap::g_inputSystem.GetKeyState(wrap::key_escape) == wrap::InputSystem::KeyState::Pressed) quit = true;
		
		wrap::g_renderer.BeginFrame();

		wrap::g_renderer.Draw(texture, { 0, 0 }, 0);

		wrap::g_renderer.EndFrame();
	}

	wrap::g_renderer.Shutdown();
	wrap::g_audio.Shutdown();
}