#pragma once
#include "Renderer.h"
#include <vector>
#include <string>

namespace wrap
{
	class Model
	{
	public:
		Model() = default;
		Model(const std::vector<wrap::Vector2>& points, const wrap::Color& color)  :
			m_points{ points },
			m_color{ color }
		{			
		}
		Model(const std::string& filename);

		void Draw(Renderer& renderer, const Vector2& position, float angle, const Vector2& scale);

		void Load(const std::string& filename);

		float CalculateRadius();
		float GetRadius() { return m_radius; }

	private:
		wrap::Color m_color{0, 0, 0, 0};
		std::vector<wrap::Vector2> m_points;

		float m_radius = 0;
	};
}