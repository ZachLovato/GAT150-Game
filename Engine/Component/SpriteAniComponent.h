#pragma once
#include "Component/RenderComponent.h"
#include <map>

namespace wrap
{
	class Texture;

	class SpriteAniComponent : public RenderComponent
	{
	public:

		struct Sequence
		{
			std::string name;

			float fps = 12;
			int num_columns = 0;
			int num_rows = 0;

			int start_frame = 0;
			int end_frame = 0;

			bool loop = true;

			std::shared_ptr<Texture> texture;
		};

		virtual void Update() override;
		virtual void Draw(Renderer& renderer) override;

		CLASS_DECLARATION(SpriteAniComponent)


		// Inherited via RenderComponent
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		Rect& GetSource() override;
		virtual void SetSequence(const std::string& name);

		int frame = 0;
		float frameTimer = 0;

		std::map<std::string, Sequence> m_sequences;
		Sequence* m_sequence = nullptr;
	};
}