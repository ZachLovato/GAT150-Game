#pragma once
#include "Component/RenderComponent.h"

namespace wrap
{
	class Texture;

	class SpriteComponent : public RenderComponent
	{
	public:
		virtual void Update() override;
		virtual void Draw(Renderer& renderer) override;

	//shared texture to a model in a model comonent
		std::shared_ptr<Texture> m_texture;
	protected:

	};
}