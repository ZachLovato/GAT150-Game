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

	rapidjson::Document document;
	bool success = wrap::json::Load("json.txt", document);
	assert(success);

	std::string str;
	wrap::json::Get(document, "string", str);
	std::cout << str << std::endl;

	bool b;
	wrap::json::Get(document, "boolean", b);
	std::cout << b << std::endl;

	int i1;
	wrap::json::Get(document, "integer1", i1);
	std::cout << i1 << std::endl;

	int i2;
	wrap::json::Get(document, "integer2", i2);
	std::cout << i2 << std::endl;

	float f;
	wrap::json::Get(document, "float", f);
	std::cout << f << std::endl;

	wrap::Vector2 v2;
	wrap::json::Get(document, "vector2", v2);
	std::cout << v2 << std::endl;

	wrap::Color color;
	wrap::json::Get(document, "color", color);
	std::cout << color << std::endl;


	//create window
	wrap::g_renderer.CreateWindow("Game", 800, 600);
	wrap::g_renderer.SetClearColor(wrap::Color{ 0 , 0 , 0 , 0 });

	//create Actors
	wrap::Scene scene;

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