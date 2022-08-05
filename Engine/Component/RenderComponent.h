#pragma once
#include "FrameWork/Component.h"

namespace wrap
{
	class Renderer;

	class RenderComponent : public Component
	{
	public:
		virtual void Draw(Renderer& renderer) = 0;

	};
}