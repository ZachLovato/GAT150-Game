#include "MyGame.h"
#include "Engine.h"
#include "../Game/GameComponents/EnemyComponent.h"

#include <iostream>

void MyGame::Initialize()
{
	REGISTER_CLASS(EnemyComponent);

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
	
	

	wrap::g_eventManager.Subscribe("EVENT_ADD_POINTS", std::bind(&MyGame::OnNotify, this, std::placeholders::_1));
	wrap::g_eventManager.Subscribe("EVENT_PLAYER_DEAD", std::bind(&MyGame::OnNotify, this, std::placeholders::_1));

}

void MyGame::Shutdown()
{
	m_scene->Removeall();
}

void MyGame::Update()
{
	switch (m_gameState)
	{
	case MyGame::gameState::titleScreen:
		if (wrap::g_inputSystem.GetKeyState(wrap::key_space) == wrap::InputSystem::KeyState::Pressed)
		{
			m_scene->GetActorFromName("Text")->SetActive(false);

			m_gameState = gameState::startLevel;
		}
		break;

	case MyGame::gameState::game:
		

		break;

	case MyGame::gameState::playerDead:
		m_stateTimer -= wrap::g_time.deltaTime;
		if (m_stateTimer <= 0)
		{
			m_gameState = (m_lives > 0) ? gameState::startLevel : gameState::gameOver;
		}

		break;

	case MyGame::gameState::startLevel:

		

		for (int i = 0; i < 1; i++)//spawns player
		{
			auto actor = wrap::Factory::Instance().Create<wrap::Actor>("Player");
			actor->m_transform.position = { 400 , 100 };
			actor->Initialize();
			m_scene->Add(std::move(actor));
		}

		for (int i = 0; i < 3; i++)//spawns "Coins"
		{
			auto actor = wrap::Factory::Instance().Create<wrap::Actor>("oil");
			actor->m_transform.position = { wrap::random(100, 700), 100 };
			actor->Initialize();
			m_scene->Add(std::move(actor));
		}

		for (int i = 0; i < 0; i++)//spawns Ghosts
		{
			auto actor = wrap::Factory::Instance().Create<wrap::Actor>("ghost");
			actor->m_transform.position = { wrap::random(100, 700), -200 };
			actor->Initialize();
			m_scene->Add(std::move(actor));
		}

		m_gameState = gameState::game;
		break;

	case MyGame::gameState::gameOver:
		break;

	default:
		break;
	}

	m_scene->Update();

}

void MyGame::Draw(wrap::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void MyGame::OnAddPoints(const wrap::Event& event)
{
	std::cout << event.name << std::endl;
	std::cout << std::get<int>(event.data) << std::endl;
	std::cout << GetScore() << std::endl;
}

void MyGame::OnPlayerDead(const wrap::Event& event)
{
	m_gameState = gameState::playerDead;
	m_stateTimer - 3.0f; 
	m_lives--;
}

void MyGame::OnNotify(const wrap::Event& event)
{
	if (event.name == "EVENT_ADD_POINTS")
	{
		AddPoints(std::get<int>(event.data));
	}

	if (event.name == "EVENT_PLAYER_DEAD")
	{
		m_gameState = gameState::playerDead;
		m_lives--;
		m_stateTimer = 3;
	}
}
