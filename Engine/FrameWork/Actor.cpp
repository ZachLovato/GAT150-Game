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

		for (auto& child : m_children)
		{
			child->Update();
		}

		if (m_parent) m_transform.Update(m_parent->m_transform.matrix);
		else m_transform.Update();
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

		for (auto& child : m_children)
		{
			child->Draw(renderer);
		}

	}

	void Actor::AddChild(std::unique_ptr<Actor> child)
	{
		child-> m_parent = this;
		child-> m_scene = m_scene;
		m_children.push_back(std::move(child));

	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		m_componets.push_back(std::move(component));
	}

}

