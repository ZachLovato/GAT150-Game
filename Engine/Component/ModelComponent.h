#pragma once

#include "Component/RenderComponent.h"

namespace wrap
{
	class Model;

	class ModelComponent : public RenderComponent
	{
	public:
		virtual void Update() override;
		virtual void Draw(Renderer& renderer) override;

		//shared texture to a model in a model comonent
		std::shared_ptr<Model> m_model;
	protected:

	};
}