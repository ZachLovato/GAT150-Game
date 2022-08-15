#include "ModelComponent.h"
#include "Renderer/Renderer.h"
#include "FrameWork/Actor.h"

namespace wrap
{
	void ModelComponent::Update()
	{

	}

	void ModelComponent::Draw(Renderer& renderer)
	{
		//renderer.Draw(m_texture, m_owner->m_transform);
		m_model->Draw(renderer, m_owner->m_transform);
	}

}
