#include "Engine.h"
#include <iostream>

int add(int a, int b)
{
	return a + b;
}

constexpr int add_c(int a, int b)
{
	return a + b;
}

int main() {
	constexpr int i = 5;

	int i2 = add(6, 7);
	int i3 = add_c(6, 7);

	float degrees = math::RadToDeg(math::Pi);

	
	wrap::InitializeMemory();
	wrap::g_inputSystem.Initialize();
	wrap::g_renderer.Initailized();
	wrap::g_audio.Initialize();

	wrap::SetFilePath("../Assets");

	wrap::g_renderer.CreateWindow("Game", 800, 600);
	wrap::g_renderer.SetClearColor(wrap::Color{ 0,0,0,0 });

	
	std::shared_ptr<wrap::Texture> texture = std::make_shared<wrap::Texture>();
	texture->Create(wrap::g_renderer, "Orber.png");

	float angle = 0;

	bool quit = false;
	while (!quit)
	{
		// update (engine)
		wrap::g_time.Tick();
		wrap::g_inputSystem.Update();
		wrap::g_audio.Update();

		if (wrap::g_inputSystem.GetKeyState(wrap::key_escape) == wrap::InputSystem::KeyState::Pressed) quit = true;
		
		angle += 720.0f * wrap::g_time.deltaTime;

		wrap::g_renderer.BeginFrame();

		wrap::g_renderer.Draw(texture, { 400, 300 }, angle, {5.0f , 5.0f}, {0.5f, 1.0f});

		wrap::g_renderer.EndFrame();
	}

	wrap::g_renderer.Shutdown();
	wrap::g_audio.Shutdown();
}