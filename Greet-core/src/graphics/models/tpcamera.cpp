#include "tpcamera.h"

namespace greet { namespace model {

	TPCamera::TPCamera()
		: m_distance(15), m_height(0), m_rotation(0)
	{
		m_position = math::vec3(0,0,0);
		event::EventDispatcher::addMouseListener(0,*this);
		m_rotationVector.z = 0;
		calculateRotationVector();
		calculateViewMatrix();
	}

	TPCamera::~TPCamera()
	{
		event::EventDispatcher::removeMouseListener(*this);
	}

	math::vec3 TPCamera::getRotationVector() const 
	{ 
		return m_rotationVector;
	}
	math::mat4 TPCamera::getViewMatrix() const 
	{ 
		return m_viewMatrix;
	}

	void TPCamera::setDistanceClamp(float min, float max)
	{
		m_distanceMin = min < 0 ? 0 : min;
		m_distanceMax = max < 0 ? 0 : max;
		calculateInformation();
	}

	void TPCamera::setHeightClamp(float min, float max)
	{
		math::clamp(&min, -1, 1);
		m_heightMin = min;
		math::clamp(&max, -1, 1);
		m_heightMax = max;
		calculateInformation();
	}

	void TPCamera::setPosition(math::vec3 pos)
	{
		m_position = pos;
		calculateInformation();
	}

	void TPCamera::calculateRotationVector()
	{
		m_rotationVector.x = math::toDegrees(asin(m_height));
		m_rotationVector.y = m_rotation;
	}

	void TPCamera::calculateViewMatrix()
	{
		m_viewMatrix = math::mat4::tpCamera(m_position, m_distance, m_height, m_rotation);
	}

	void TPCamera::calculateInformation()
	{
		calculateRotationVector();
		calculateViewMatrix();
	}

	bool TPCamera::onPressed(const event::MousePressedEvent& e){
		if (e.getButton() == GLFW_MOUSE_BUTTON_1)
		{
			m_mouse1 = true;
		}
		if (e.getButton() == GLFW_MOUSE_BUTTON_3)
		{
			m_mouse3 = true;
		}
		return false;
	}

	bool TPCamera::onReleased(const event::MouseReleasedEvent& e)
	{
		if (e.getButton() == GLFW_MOUSE_BUTTON_1)
		{
			m_mouse1 = false;
		}
		if (e.getButton() == GLFW_MOUSE_BUTTON_3)
		{
			m_mouse3 = false;
		}
		return false;
	}

	bool TPCamera::onMoved(const event::MouseMovedEvent& e) {
		if (m_mouse3) {
			m_height += e.getDY() * m_heightSpeed;
			math::clamp(&m_height, m_heightMin, m_heightMax);
			m_rotation += e.getDX() * m_rotationSpeed;
			calculateInformation();
		}
		else if (m_mouse1)
		{
			math::vec2 dpos = e.getDeltaPosition();
			dpos.rotate(m_rotation);
			m_position.x += dpos.y * m_distanceSpeed * m_distance;
			m_position.z -= dpos.x * m_distanceSpeed * m_distance;
			calculateInformation();
		}
		return false;
	}

	bool TPCamera::onScroll(const event::MouseScrollEvent& e) {
		m_distance -= e.getScroll();
		math::clamp(&m_distance, m_distanceMin, m_distanceMax);
		calculateInformation();
		return false;
	}

} }