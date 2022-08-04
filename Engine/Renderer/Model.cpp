#include "Model.h"
#include "../Core/file.h"
#include <iostream>
#include <sstream>

namespace wrap 
{
	Model::Model(const std::string& filename)
	{
		Load(filename);
		m_radius = CalculateRadius();
	}

	void Model::Draw(Renderer& renderer, const Vector2& position, float angle, const Vector2& scale)
	{
		for (int i = 0; i < m_points.size() - 1; i++)
		{
			wrap::Vector2 p1 = Vector2::Rotate((m_points[i] * scale), angle) + position;
			wrap::Vector2 p2 = Vector2::Rotate((m_points[i + 1] * scale), angle) + position;

			renderer.DrawLine(p1, p2, m_color);
			//renderer.DrawLine(p1, p1, m_color);
		}
	}

	void Model::Load(const std::string& filename)
	{
		std::string buffer;
		wrap::ReadFile(filename, buffer);

		// Read Color
		std::istringstream stream(buffer);
		stream >> m_color;

		// read the number of points
		std::string line;
		std::getline(stream, line);


		// here is the error
		size_t numPoints = std::stoi(line);

		//read model points
		for (size_t i = 0; i < numPoints; i++)
		{
			Vector2 point;

			stream >> point;

			m_points.push_back(point);
		}
	}
	float Model::CalculateRadius()
	{
		float radius = 0;

		//find the verticies length
		for (auto& point : m_points)
		{
			if (point.Length() > radius) radius = point.Length();
		}

		return radius;
	}

}