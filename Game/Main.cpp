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
		
	//resources
	std::shared_ptr<wrap::Texture> texture = std::make_shared<wrap::Texture>();
	texture->Create(wrap::g_renderer, "Sprites/Orber.png");

	wrap::g_audio.AddAudio("bg", "rocket.wav");

	//std::shared_ptr<wrap::Model> model = std::make_shared<wrap::Model>();
	//model->Create("Sprites/Player.txt");

	
	std::shared_ptr<wrap::Model> model2 = wrap::g_resources.Get<wrap::Model>("Player.txt");

	//create Actors
	wrap::Scene scene;

	wrap::Transform transform{ wrap::Vector2{ 400 , 300 }, 90, { 3 , 3 } };
	//std::unique_ptr<wrap::Actor> actor = std::make_unique<wrap::Actor>();
	std::unique_ptr<wrap::Actor> actor = wrap::Factory::Instance().Create<wrap::Actor>("Actor");
	actor->m_transform = transform;

	std::unique_ptr<wrap::Component> pcomponent = wrap::Factory::Instance().Create<wrap::PlayerComponent>("PlayerComponent");
	actor->AddComponent(std::move(pcomponent));


	std::unique_ptr<wrap::ModelComponent> mcomponent = std::make_unique<wrap::ModelComponent>();
	mcomponent->m_model = model2;
	actor->AddComponent(std::move(mcomponent));

	//std::unique_ptr<wrap::SpriteComponent> sprcomponent = std::make_unique<wrap::SpriteComponent>();
	//std::shared_ptr<wrap::Texture> texture = wrap::g_resources.Get<wrap::Texture>("name", wrap::g_renderer);
	//sprcomponent->m_texture = texture;
	//actor->AddComponent(std::move(sprcomponent));


	std::unique_ptr<wrap::AudioComponent> acomponent = std::make_unique<wrap::AudioComponent>();
	acomponent->m_soundName = "bg";
	actor->AddComponent(std::move(acomponent));

	std::unique_ptr<wrap::Component> phcomponent = wrap::Factory::Instance().Create<wrap::Component>("PhysicsComponent");
	actor->AddComponent(std::move(phcomponent));


	//Child Actor
	wrap::Transform transformC{ wrap::Vector2{10,10}, 0, {1,1} };
	std::unique_ptr<wrap::Actor> child = std::make_unique<wrap::Actor>(transformC);

	std::unique_ptr<wrap::ModelComponent> mccomponent = std::make_unique<wrap::ModelComponent>();
	mccomponent->m_model = model2;
	child->AddComponent(std::move(mccomponent));

	actor->AddChild(std::move(child));

	//actor
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