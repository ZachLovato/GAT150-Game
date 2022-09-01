#pragma once
#include "FrameWork/Game.h"
#include "FrameWork/Event.h"


class MyGame : public wrap::Game, public wrap::INotify 
{
public:
	enum class gameState
	{
		titleScreen,
		game,
		playerDead,
		startLevel,
		gameOver,

	};

	virtual void Initialize() override;
	virtual void Shutdown() override;
	virtual void Update() override;
	virtual void Draw(wrap::Renderer& renderer) override;
	virtual void OnNotify(const wrap::Event& event) override;

	void OnAddPoints(const wrap::Event& event);
	void OnPlayerDead(const wrap::Event& event);


private:
	gameState m_gameState = gameState::titleScreen;
	float m_stateTimer = 3;
	int m_lives = 3;


	// Inherited via INotify


	// Inherited via INotify

};