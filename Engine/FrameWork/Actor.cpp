#include "Actor.h"
#include "Component/RenderComponent.h"
#include "Factory.h"

namespace wrap 
{
	void Actor::Initialize()
	{
		for (auto& component : m_componets)
		{
			component->Initialize();
		}

		for (auto& child : m_children)
		{
			child->Initialize();
		}
	}

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

	bool Actor::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool Actor::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, tag);
		READ_DATA(value, name);

		m_transform.Read(value["transform"]);
		if (value.HasMember("components") && value["components"].IsArray())
		{
			for (auto& componentValue : value["components"].GetArray())
			{
				std::string type;
				READ_DATA(componentValue, type);

				auto component = Factory::Instance().Create<Component>(type);
				if (component)
				{
					component->Read(componentValue);
					AddComponent(std::move(component));
				}

			}
		}


		return true;
	}

}

