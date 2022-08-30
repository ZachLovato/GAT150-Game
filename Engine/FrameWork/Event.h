#pragma once
#include <string>
#include <variant>
#include <functional>

namespace wrap
{
	class GameObjects;

	class Event
	{
	public:
		using functionPtr = std::function<void(const Event&)>;

	public:
		std::string name;
		GameObjects* receiver = nullptr;
		std::variant<int, bool, float, std::string> data;

	};
}