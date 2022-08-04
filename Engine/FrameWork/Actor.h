#pragma once
#include "GameObject.h"
#include "../Renderer/Model.h"

namespace wrap
{
	class Scene;

	class Actor : public GameObjects
	{
	public:
		Actor() = default;
		Actor(const Model& model, const Transform& transform) : 
			GameObjects{ transform }, 
			m_model{ model } {}

		virtual void Update() override {}
		virtual void Draw(Renderer& renderer);

		virtual void OnCollision(Actor* other) {}
		float GetRadius() { return m_model.GetRadius() * std::max( m_transform.scale.x, m_transform.scale.y); }
		std::string& GetTag() { return m_tag; }

		friend class Scene;

	protected:
		std::string m_tag;
		bool m_destroy = false;
		//physics
		Vector2 m_velocity;
		float m_damping = .7f;

		Scene* m_scene = nullptr;
		Model m_model;
	};
}