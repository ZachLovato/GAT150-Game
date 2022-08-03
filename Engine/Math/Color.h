#pragma once
#include <cstdint>
#include <iostream>

namespace wrap
{
	using u8_t = unsigned char;
	struct Color
	{
		uint8_t r = 255;
		uint8_t g = 255;
		uint8_t b = 255;
		uint8_t a = 255;

		friend std::istream& operator >> (std::istream& stream, Color& c);
	};

	inline std::istream& operator >> (std::istream& stream, Color& c)
	{
		std::string line;
		std::getline(stream, line);

		std::string str;

		str = line.substr(line.find("{") + 1, line.find(",") - 1);
		std::cout << str << std::endl;
		c.r = (uint8_t)(std::stof(str) * 255);


		str = line.substr(line.find(",") + 1, line.find(",") + line.find(","));
		std::cout << str << std::endl;
		c.g = (uint8_t)(std::stof(str) * 255);


		
		str = line.substr(line.find(",") + 1, line.find("}") - 1);
		std::cout << str << std::endl;
		c.b = (uint8_t)(std::stof(str) * 255);
		//c.b = (uint8_t)(std::stof(str) * 255);

		c.a = 255;

		return stream;
	}

}