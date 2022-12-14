#include "Scene.h"
#include "Factory.h"

#include <algorithm>
#include <iostream>

namespace wrap
{
	void Scene::Update()
	{
		auto iter = m_actors.begin();
		while (iter != m_actors.end())
		{
			(*iter)->Update();
			if ((*iter)->m_destroy)
			{
				iter = m_actors.erase(iter);
			}
			else
			{
				iter++;
			}
		}

	}

	void Scene::Initialize()
	{
		for (auto& actor : m_actors) (actor->Initialize());
	}

	void Scene::Draw(Renderer& renderer)
	{
		for (auto& actor : m_actors) 
		{
			actor->Draw(renderer);
		}
	}

	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::Removeall()
	{
		for (auto& actor : m_actors) { actor->SetDestory(); }
		m_actors.clear();
	}

	bool Scene::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool Scene::Read(const rapidjson::Value& value)
	{
		if (!value.HasMember("actors") && !value["actors"].IsArray())
		{
			return false;
		}

		for (auto& actorValue : value["actors"].GetArray())
		{
			std::string type;
			READ_DATA(actorValue, type);
			//wrap::json::Get(actorValue, "type", type);

			auto actor = Factory::Instance().Create<Actor>(type);
			if (actor)
			{
				// read actor
				actor->Read(actorValue);

				bool preFab = false;
				READ_DATA(actorValue, preFab);

				if (preFab)
				{
					std::string name = actor->GetName();
					Factory::Instance().RegisterPreFab(name, std::move(actor));
				}
				else
				{
					Add(std::move(actor));

				}

			}


		}

		return true;
	}

}
