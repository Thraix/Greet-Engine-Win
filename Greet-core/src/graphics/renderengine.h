#pragma once

#include <map>
#include <graphics/layers/layer.h>
#include <graphics/layers/layer3d.h>
#include <graphics/layers/guilayer.h>

namespace greet { namespace graphics {
	class RenderEngine
	{

	private:
		static std::map<std::string, Layer*> m_renderer2ds;
		static std::map<std::string, Layer3D*> m_renderer3ds;

	public:
		static void add_layer2d(Layer* renderer, const std::string& name);
		static void add_layer3d(Layer3D* renderer, const std::string& name);

		static Layer* remove_layer2d(const std::string& name);
		static Layer3D* remove_layer3d(const std::string& name);
		static Layer* get_renderer2d(const std::string& name);
		static Layer3D* get_renderer3d(const std::string& name);
		static void render();
		static void update(float timeElapsed);


		
	};
}}