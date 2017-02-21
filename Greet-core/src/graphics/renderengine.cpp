#include "renderengine.h"

namespace greet { namespace graphics {

	std::map<std::string, Layer<Renderable>*> RenderEngine::m_renderer2ds;
	std::map<std::string, Layer3D*> RenderEngine::m_renderer3ds;

	void RenderEngine::add_layer2d(Layer<Renderable>* renderer, const std::string& name)
	{
		m_renderer2ds.emplace(name, renderer);
	}

	void RenderEngine::add_layer3d(Layer3D* renderer, const std::string& name)
	{
		m_renderer3ds.emplace(name, renderer);
	}

	Layer<Renderable>* RenderEngine::remove_layer2d(const std::string& name)
	{
		auto it = m_renderer2ds.find(name);
		m_renderer2ds.erase(it);
		return it->second;
	}

	Layer3D* RenderEngine::remove_layer3d(const std::string& name)
	{
		auto it = m_renderer3ds.find(name);
		m_renderer3ds.erase(it);
		return it->second;
	}

	Layer<Renderable>* RenderEngine::get_renderer2d(const std::string& name)
	{
		auto it = m_renderer2ds.find(name);
		return it->second;
	}

	Layer3D* RenderEngine::get_renderer3d(const std::string& name)
	{
		auto it = m_renderer3ds.find(name);
		return it->second;
	}

	void RenderEngine::render()
	{
		for (auto it = m_renderer3ds.begin(); it != m_renderer3ds.end(); it++)
		{
			it->second->render();
		}

		for (auto it = m_renderer2ds.begin(); it != m_renderer2ds.end(); it++)
		{
			it->second->render();
		}
	}

	void RenderEngine::update(float timeElapsed)
	{
		for (auto it = m_renderer3ds.begin(); it != m_renderer3ds.end(); it++)
		{
			it->second->update(timeElapsed);
		}

		for (auto it = m_renderer2ds.begin(); it != m_renderer2ds.end(); it++)
		{
			it->second->update(timeElapsed);
		}
	}

} }