#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "FrameWork/Actor.h"

namespace wrap
{
	void wrap::SpriteComponent::Update()
	{

	}

	void wrap::SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.Draw(m_texture, m_owner->m_transform);
	}

}
