#pragma once
#include "Actor.h"
#include <list>
#include <memory>

namespace wrap
{
	// Forward declaration
	class Actor;
	class Renderer;
	class Game;

	class Scene : public GameObject, public ISerializable
	{
	public:
		Scene() = default;
		Scene(Game* game) : m_game{ game } {}
		Scene(const Scene& other) {}
		~Scene() = default; 

		CLASS_DECLARATION(Scene)

		void Update() override;
		void Initialize() override;
		void Draw(Renderer& renderer );

		void Add(std::unique_ptr<Actor> actor);
		void Removeall();

		template<typename T>
		T* GetActor();

		virtual bool Write(const rapidjson::Value& value) const override;

		virtual bool Read(const rapidjson::Value& value) override;
		
		Game* GetGame() { return m_game; }

	private:
		Game* m_game = nullptr;
		std::list<std::unique_ptr<Actor>> m_actors;




	};

	template<typename T>
	inline T* Scene::GetActor()
	{
		//int i = 45;
		//float f = static_cast(float)34;
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result;
		}

		return nullptr;
	}
}