#include "Color.h"
#include <string>

namespace wrap
{
	const Color white{ 0 , 0 , 0 , 0 };
	const Color black{ 255 , 255 , 255 , 255 };
	const Color red{ 255 , 0 , 0 , 0 };
	const Color green{ 0 , 255 , 0 , 0 };
	const Color blue{ 0 , 0 , 255 , 0 };
	const Color teal{0 , 128 , 128 , 0 };

	std::istream& operator >> (std::istream& stream, Color& c)
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