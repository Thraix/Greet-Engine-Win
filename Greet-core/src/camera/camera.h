#pragma once

#include <internal/greet_types.h>
#include <internal/greetgl.h>
#include <graphics/layers/layer.h>
#include <graphics/window.h>
#include <listeners/windowresize.h>

namespace greet { namespace camera {

	struct LayerIndex
	{
		LayerIndex(graphics::Layer* l, uint i) : layer(l), index(i) {}
		~LayerIndex() { delete layer; }
		graphics::Layer* layer;
		uint index;
	};

	class Camera : public listener::WindowResizeListener
	{
	public:
	private:
		std::vector<LayerIndex*> m_layers;
		math::Transform m_transform;
		graphics::Window* m_window;
	public:
		virtual ~Camera();
		void addLayer(graphics::Layer* layer,uint layerIndex);
		void removeLayer(uint layerIndex);
		graphics::Layer* getLayer(uint layerIndex) const;
		void render() const;
		void update(float timeElapsed);
		void windowResize(int width, int height);
		void setViewport(float x, float y, float width, float height);

	private:
		Camera(graphics::Window* window);
	public:
		static void initCamera(graphics::Window* window);
		static void destroyCamera();
		static Camera* getInstance();
	private:
		static Camera* instance;

	};
}}
