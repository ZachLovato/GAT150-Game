#pragma once
#include "FrameWork/Game.h"

class MyGame : public wrap::Game
{
public:
	// Inherited via Game
	virtual void Initialize() override;
	virtual void Shutdown() override;
	virtual void Update() override;
	virtual void Draw(wrap::Renderer& renderer) override;
};