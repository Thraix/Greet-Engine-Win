#pragma once

#include <vector>
#include <graphics/atlas/atlas.h>
#include <logging/log.h>
#include <internal/Greet_types.h>
#include <utils/errorhandler.h>

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
