#pragma once
#include "FrameWork/Component.h"
#include "Math/Rect.h"

namespace wrap
{
	class Renderer;

	class RenderComponent : public Component
	{
	public:


		virtual void Draw(Renderer& renderer) = 0;
		virtual void Update() override;

		virtual Rect& GetSource() { return source; }

	protected:
		Rect source;

	};
}