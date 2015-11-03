#pragma once

#include <vector>
#include <graphics/atlas/atlas.h>
#include <utils/log.h>
#include <greet_types.h>

namespace greet {namespace managers {
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