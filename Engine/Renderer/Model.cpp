#include "Model.h"
#include "../Core/file.h"
#include "Core/Logger.h"
#include "Math/Transform.h"
#include "Math/MathUtils.h"
#include "Math/Color.h"
#include <iostream>
#include <sstream>

namespace wrap 
{
	Model::Model(const std::string& filename)
	{
		Load(filename);
		m_radius = CalculateRadius();
	}

	bool Model::Create(const std::string& filename, void* data)
	{
		if (!Load(filename))
		{
			LOG("ERROR Could Not Read File %s", filename.c_str());
			return false;
		}
			return true;
	}

	void Model::Draw(Renderer& renderer, const Vector2& position, float angle, const Vector2& scale)
	{
		for (size_t i = 0; i < m_points.size() - 1; i++)
		{
			wrap::Vector2 p1 = Vector2::Rotate((m_points[i] * scale), angle) + position;
			wrap::Vector2 p2 = Vector2::Rotate((m_points[i + 1] * scale), angle) + position;

			renderer.DrawLine(p1, p2, m_color);
			//renderer.DrawLine(p1, p1, m_color);
		}
	}

	void Model::Draw(Renderer& renderer, const Transform& transform)
	{
		Matrix3x3 mx = transform.matrix;
		if (m_points.size() == 0) return;

		for (int i = 0; i < m_points.size() - 1; i++)
		{
			wrap::Vector2 p1 = mx * m_points[i];
			wrap::Vector2 p2 = mx * m_points[i + 1];

			renderer.DrawLine(p1, p2, m_color);
		}
	}

	//error here with the model load function
	bool Model::Load(const std::string& filename)
	{
		std::string buffer;
		wrap::ReadFile(filename, buffer);

		if (!wrap::ReadFile(filename, buffer))
		{
			LOG("ERROR Could Not Read File %s", filename.c_str());
			return false;
		}

		// Read Color
		std::istringstream stream(buffer);
		// here is the error
		stream >> m_color;

		// read the number of points
		std::string line;
		std::getline(stream, line);


		size_t numPoints = std::stoi(line);

		//read model points
		for (size_t i = 0; i < numPoints; i++)
		{
			Vector2 point;

			stream >> point;

			m_points.push_back(point);
		}

		return true;
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

};