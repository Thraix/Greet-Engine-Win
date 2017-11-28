#pragma once

#include <graphics/Window.h>
#include <vector>
#include <random>
#include <ctime>

namespace Greet {


	class UUID 
	{
		friend class Window;
	private:
		uint m_current;
		std::vector<uint> m_usedUUID;

		UUID();
		~UUID() { }

	public:
		uint getUUID();
	public:
		static UUID* getInstance() { return s_instance; }
	private:

		static UUID* s_instance;

		static void init();
		static void cleanUp();
	};
}