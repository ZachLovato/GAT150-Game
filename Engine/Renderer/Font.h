#pragma once
#include "Resource/Resource.h"
#include <string>

struct _TTF_Font;

namespace wrap
{
	class Font : public Resource
	{
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();

		bool Create(const std::string filename, void* data = nullptr) { return false; }
		void Load(const std::string& filename, int fontSize);

	private:
		_TTF_Font* m_ttfFont = nullptr;
		friend class Text;
	};
}