#pragma once
#include "Component/RenderComponent.h"

namespace wrap
{
	class Texture;

	class SpriteAniComponent : public RenderComponent
	{
	public:
		virtual void Update() override;
		virtual void Draw(Renderer& renderer) override;

		CLASS_DECLARATION(SpriteAniComponent)


		// Inherited via RenderComponent
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		Rect& GetSource() override;

		// json animation values
		float fps = 0.0f;
		int num_colums = 0;
		int num_rows = 0;

		int start_frame = 0;
		int end_frame = 0;
		
		int frame = 0;
		float frameTimer = 0;

		std::shared_ptr<Texture> m_texture;

	};
}