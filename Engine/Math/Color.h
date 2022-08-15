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

		static const Color white;
		static const Color black;
		static const Color red;
		static const Color green;
		static const Color blue;
		static const Color teal;

	};

	std::istream& operator >> (std::istream& stream, Color& c);

}