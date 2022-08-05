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



		std::shared_ptr<Texture> m_texture;
	protected:

	};
}