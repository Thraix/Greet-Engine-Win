#pragma once

#include <vector>
#include <graphics/atlas/atlas.h>
#include <logging/logger.h>
#include <internal/greet_types.h>

namespace greet {namespace graphics {
	class AtlasManager
	{
	private:
		static std::vector<graphics::Atlas*> m_atlas;
	public:
		static void add(graphics::Atlas* atlas);
		static graphics::Atlas* get(const std::string& atlasname);
		static void destroy();
	private:
		AtlasManager(){}
	};
}}
