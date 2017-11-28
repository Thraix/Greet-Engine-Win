#pragma once

#include <vector>
#include <graphics/atlas/Atlas.h>
#include <logging/Log.h>
#include <internal/GreetTypes.h>
#include <utils/ErrorHandler.h>

namespace Greet {
	class AtlasManager
	{
	private:
		static std::vector<Atlas*> m_atlas;
	public:
		static void add(Atlas* atlas);
		static Atlas* get(const std::string& atlasname);
		static void destroy();
	private:
		AtlasManager(){}
	};
}
