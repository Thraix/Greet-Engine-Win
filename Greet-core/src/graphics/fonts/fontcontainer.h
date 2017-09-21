#pragma once

#include <internal\Greet_types.h>
#include <string>
#include <vector>

namespace Greet{

	class Font;
	class FontContainer
	{
	friend class Font;

	private:
		const byte* m_data;
		uint m_datasize;
		std::string m_name;
		std::string m_filename;
		std::vector<Font*> m_fonts;

	public:
		FontContainer(const std::string& filename, const std::string& name);
		FontContainer(const byte* data, uint datasize, const std::string& name);
		virtual ~FontContainer();

		Font* getSize(uint size);

		inline const std::string& getName() const { return m_name; }
		inline const std::string& getFileName() const { return m_filename; }
		inline const byte* getData() const { return m_data;}
		inline uint getDataSize() const { return m_datasize;}

	};
}