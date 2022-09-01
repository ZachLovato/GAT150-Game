#pragma once
#include "GameObject.h"
#include "Component.h"
#include "Math/Transform.h"
#include "Renderer/Model.h"
#include <vector>

namespace wrap
{
	class Scene;
	class Component;
	class Renderer;

	class Actor : public GameObject, public ISerializable
	{
	public:
		Actor() = default;
		Actor(const Actor& other);
		Actor(const Transform& transform) : m_transform{ transform } {}

		CLASS_DECLARATION(Actor)
		
		void Initialize() override;
		virtual void Update() override;
		virtual void Draw(Renderer& renderer);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void AddChild(std::unique_ptr<Actor> child);

		void AddComponent(std::unique_ptr<Component> compone);
		template<typename T>
		T* GetComponent();
		
		const std::string& GetTag() { return tag; }
		void SetTag(const std::string& tag) { this->tag = tag; }
		
		const std::string& GetName() { return name; }
		void SetName(const std::string& name) { this->name = name; }

		void SetDestory() { m_destroy = true; }
		bool IsDestory() { return m_destroy; }

		void SetActive(bool active) { this->active = active; }
		bool IsActive() { return active; }

		Scene* GetScene() { return m_scene; }

		friend class Scene;
		friend class Component;

		Transform m_transform;


	protected:
		std::string name;
		std::string tag;

		bool m_destroy = false;
		bool active = true;
		float lifespans = 0.0f;

		Scene* m_scene = nullptr;
		Actor* m_parent = nullptr;

		std::vector<std::unique_ptr <Component>> m_componets;
		std::vector<std::unique_ptr <Actor>> m_children;

	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : m_componets)
		{
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}
		return nullptr;
	}


}