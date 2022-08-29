#include "MyGame.h"
#include "Engine.h"

#include <iostream>

void MyGame::Initialize()
{
	m_scene = std::make_unique<wrap::Scene>();

	rapidjson::Document document;
	std::vector<std::string> sceneNames = { "Scene/preFab.txt", "Scene/level.txt", "Scene/Tilemap.txt"};

	for (auto sceneName : sceneNames)
	{
		bool success = wrap::json::Load(sceneName, document);
		if (!success) 
		{ 
			LOG("Could Not Load Scene Name %s", sceneName.c_str()); 
			continue;
		}
		m_scene->Read(document);
	}
	m_scene->Initialize();

	for (int i = 0; i < 10; i++)
	{
		auto actor = wrap::Factory::Instance().Create<wrap::Actor>("oil");
		actor->m_transform.position = { wrap::random(0, 500), 100 };
		actor->Initialize();
		m_scene->Add(std::move(actor));
	}
}

void MyGame::Shutdown()
{
	m_scene->Removeall();
}

void MyGame::Update()
{
	m_scene->Update();
}

void MyGame::Draw(wrap::Renderer& renderer)
{
	m_scene->Draw(renderer);
}
