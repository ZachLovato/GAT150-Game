#pragma once
#include "Component/RenderComponent.h"
#include "Math/Rect.h"

namespace wrap
{
	class Texture;

	class SpriteComponent : public RenderComponent
	{
	public:
		virtual void Update() override;
		virtual void Draw(Renderer& renderer) override;

		CLASS_DECLARATION(SpriteComponent)


		// Inherited via RenderComponent
		virtual bool Write(const rapidjson::Value& value) const override;

		virtual bool Read(const rapidjson::Value& value) override;
	
		//shared texture to a model in a model comonent
		std::shared_ptr<Texture> m_texture;
	
		Rect source;
		//std::shared_ptr<Texture> m_texture;


	};
}