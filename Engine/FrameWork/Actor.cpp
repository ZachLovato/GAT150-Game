#include "Actor.h"
#include "Component/RenderComponent.h"

namespace wrap 
{
	void Actor::Update()
	{
		for (auto& component : m_componets)
		{
			component->Update();
		}
	}
	void Actor::Draw(Renderer& renderer)
	{
		//m_model.Draw(renderer, m_transform.position, m_transform.rotation, m_transform.scale);
		for (auto& component : m_componets)
		{
			auto renderComponet = dynamic_cast<RenderComponent*>(component.get());
			if (renderComponet)
			{
				renderComponet->Draw(renderer);
			}
			//component->Update();
		}

	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		m_componets.push_back(std::move(component));
	}

}

