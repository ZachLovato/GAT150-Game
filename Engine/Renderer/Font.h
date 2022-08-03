#pragma once
#include <string>

struct _TTF_Font;

namespace wrap
{
	class Font
	{
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();

		void Load(const std::string& filename, int fontSize);

	private:
		_TTF_Font* m_ttfFont = nullptr;
		friend class Text;
	};
}