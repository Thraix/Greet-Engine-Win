#if 0
#include "camera.h"
namespace greet {

	Camera* Camera::instance;

	Camera::Camera(graphics::Window* window)
		: m_window(window)
	{
		m_window->addResizeCallback(this);
	}

		Camera::~Camera()
		{
			for (std::vector<LayerIndex*>::iterator li = m_layers.begin();li != m_layers.end();++li)
			{
				delete (*li);
			}
		m_layers.clear();
	}

	// Render all layers
	void Camera::render() const
	{
		for (uint i = 0; i < m_layers.size();i++)
		{
			m_layers[i]->layer->render();
		}
	}

	// Update all layers
	void Camera::update(float timeElapsed)
	{
		for (uint i = 0; i < m_layers.size();i++)
		{
			m_layers[i]->layer->update(timeElapsed);
		}
	}

	void Camera::windowResize(int width, int height)
	{
		for (uint i = 0; i < m_layers.size();i++)
		{
			m_layers[i]->layer->windowResize(width, height);
		}
	}

	// Set the viewport of the camera
	void Camera::setViewport(float x, float y, float width, float height)
	{
		y = y + m_window->getHeight() - height;
		glViewport(x, y, width, height);
		for (uint i = 0; i < m_layers.size();i++)
		{
			m_layers[i]->layer->viewportResize(x,y,width,height);
		}
	}

	// Add a layer to the game
	void Camera::addLayer(graphics::Layer* layer, uint layerIndex)
	{
		LayerIndex* l;
		for (uint i = 0; i < m_layers.size();i++)
		{
			l = m_layers[i];
			if (l->index == layerIndex)
			{
				LOG_ERROR("CAMERA", "The given layer is already occupied. Consider removing or changing layer: ",layerIndex);
				return;
			}
			if (l->index > layerIndex)
			{
				m_layers.insert(m_layers.begin()+i,new LayerIndex(layer,layerIndex));
				return;
			}
		}
		m_layers.insert(m_layers.begin() + m_layers.size(), new LayerIndex(layer, layerIndex));
	}

	// Remove a certain layer from the game
	void Camera::removeLayer(uint layerIndex)
	{
		LayerIndex* l;
		for (uint i = 0; i < m_layers.size();i++)
		{
			l = m_layers[i];
			if (l->index == layerIndex)
			{
				m_layers.erase(m_layers.begin() + i);
			}
		}
	}

	// Get a certain layer of the game
	graphics::Layer* Camera::getLayer(uint layerIndex) const
	{
		LayerIndex* l;
		for (uint i = 0; i < m_layers.size();i++)
		{
			l = m_layers[i];
			if (l->index == layerIndex)
			{
				return l->layer;
			}
		}
		LOG_ERROR("CAMERA", "No such layer in camera: ", layerIndex);
		return NULL;
	}



	// STATIC FUNCTIONS

	// Inits the static camera
	void Camera::initCamera(graphics::Window* window)
	{
		LOG_INFO("CAMERA", "Initializing camera.");
		Camera::instance = new Camera(window);
	}

	// Destroys the static camera
	void Camera::destroyCamera()
	{
		LOG_INFO("CAMERA", "Destroying camera.");
		delete Camera::instance;
	}

	// Returns the camera instance
	Camera* Camera::getInstance()
	{
		return Camera::instance;
	}
}
#endif