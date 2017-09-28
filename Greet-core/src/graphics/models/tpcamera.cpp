#include "tpcamera.h"

namespace Greet {

	TPCamera::TPCamera()
		: TPCamera(vec3(0,0,0), 1, 0, 0)
	{
	}

	TPCamera::TPCamera(vec3 position, float distance, float height, float rotation)
		:TPCamera(position, distance, height, rotation, 1, 100, -1,1)
	{
	
	}

	TPCamera::TPCamera(vec3 position, float distance, float height, float rotation, float distanceMin, float distanceMax, float heightMin, float heightMax)
		: TPCamera(position, distance, height, rotation, distanceMin, distanceMax, heightMin, heightMax, 0.5f, 0.01f, 0.005f)
	{
	}

	TPCamera::TPCamera(vec3 position, float distance, float height, float rotation, float distanceMin, float distanceMax, float heightMin, float heightMax, float rotationSpeed, float heightSpeed, float distanceSpeed) 
		: m_position(position), m_distance(distance), m_height(height), m_rotation(rotation), m_rotationSpeed(rotationSpeed), m_heightSpeed(heightSpeed), m_distanceSpeed(distanceSpeed)
	{
		m_rotationWanted = m_rotation;
		m_rotationVector.z = 0;
		setDistanceClamp(distanceMin, distanceMax);
		setHeightClamp(heightMin, heightMax);
		calculateInformation();
		EventDispatcher::addMouseListener(0, *this);
	}

	TPCamera::~TPCamera()
	{
		EventDispatcher::removeMouseListener(*this);
	}

	void TPCamera::update(float timeElapsed)
	{
		m_rotation += (m_rotationWanted - m_rotation) * (timeElapsed * 10.0f); // 0.33 ish
		calculateInformation();
	}

	const vec3& TPCamera::getRotationVector() const
	{ 
		return m_rotationVector;
	}

	const mat4& TPCamera::getViewMatrix() const
	{ 
		return m_viewMatrix;
	}

	void TPCamera::setPosition(vec3 pos)
	{
		m_position = pos;
		calculateViewMatrix();
	}

	void TPCamera::setHeight(float height)
	{
		m_height = height;
		Math::clamp(&m_height, m_heightMin, m_heightMax);
		if (m_height != height)
		{
			Log::warning("Height outside of clamp, clamping.");
		}
		calculateInformation();
	}

	void TPCamera::setRotation(float rotation)
	{
		//m_rotation = rotation;
		m_rotationWanted = rotation; // smooth transition
		calculateViewMatrix();
	}

	void TPCamera::setDistance(float distance)
	{
		m_distance = distance;
		Math::clamp(&m_distance, m_distanceMin, m_distanceMax);
		if (m_distance != distance)
		{
			Log::warning("Distance outside of clamp, clamping.");
		}
	}

	void TPCamera::setDistanceClamp(float min, float max)
	{
		if (min > max)
		{
			Log::error("Distance clamp: min greater than max.");
			return;
		}
		m_distanceMin = min < 0 ? 0 : min;
		m_distanceMax = max < 0 ? 0 : max;
		if (m_distance < m_distanceMin)
		{
			Log::info("Distance outside of clamp, reclamping.");
			m_distance = m_distanceMin;
		}
		else if (m_distance > m_distanceMax)
		{
			Log::info("Distance outside of clamp, reclamping.");
			m_distance = m_distanceMax;
		}
	}

	void TPCamera::setHeightClamp(float min, float max)
	{
		if (min > max)
		{
			Log::error("Height clamp: min greater than max.");
			return;
		}
		Math::clamp(&min, -1, 1);
		Math::clamp(&max, -1, 1);
		m_heightMin = min;
		m_heightMax = max;
		if (m_height < m_heightMin)
		{
			Log::info("Height outside of clamp, reclamping.");
			m_height = m_heightMin;
		}
		else if (m_height > m_heightMax)
		{
			Log::info("Height outside of clamp, reclamping.");
			m_height = m_heightMax;
		}
	}

	void TPCamera::calculateRotationVector()
	{
		m_rotationVector.x = Math::toDegrees(asin(m_height));
		m_rotationVector.y = m_rotation;
	}

	void TPCamera::calculateViewMatrix()
	{
		m_viewMatrix = mat4::tpCamera(m_position, m_distance, m_height, m_rotation);
	}

	void TPCamera::calculateInformation()
	{
		calculateRotationVector();
		calculateViewMatrix();
	}

	bool TPCamera::onPressed(const MousePressedEvent& e){
		if (e.getButton() == GLFW_MOUSE_BUTTON_1)
		{
			m_mouse1 = true;
			//mat4 inv = ~m_viewMatrix;
			//vec3 worldCoord = inv * vec3(e.getX(), e.getY(), 1.0f);
			//Log::info(worldCoord.x," ", worldCoord.y);
		}
		if (e.getButton() == GLFW_MOUSE_BUTTON_3)
		{
			m_mouse3 = true;
		}
		if (e.getButton() == GLFW_MOUSE_BUTTON_2)
		{
			m_mouse2 = true;
		}
		return false;
	}

	bool TPCamera::onReleased(const MouseReleasedEvent& e)
	{
		if (e.getButton() == GLFW_MOUSE_BUTTON_1)
		{
			m_mouse1 = false;
		}
		if (e.getButton() == GLFW_MOUSE_BUTTON_2)
		{
			m_mouse2 = false;
		}
		if (e.getButton() == GLFW_MOUSE_BUTTON_3)
		{
			m_mouse3 = false;
		}
		return false;
	}

	bool TPCamera::onMoved(const MouseMovedEvent& e) {
		if (m_mouse3) {
			m_height += e.getDY() * m_heightSpeed;
			Math::clamp(&m_height, m_heightMin, m_heightMax);
			m_rotationWanted += m_rotationSpeed * e.getDX();
		}
		if (m_mouse2)
		{
			m_position.y += e.getDeltaPosition().y * 0.1f;
		}
		else if (m_mouse1)
		{
			vec2 dpos = e.getDeltaPosition();
			dpos.rotate(m_rotation);
			m_position.x += dpos.y * m_distanceSpeed * m_distance;
			m_position.z -= dpos.x * m_distanceSpeed * m_distance;
		}
		return false;
	}

	bool TPCamera::onScroll(const MouseScrollEvent& e) {
		m_distance -= e.getScroll();
		Math::clamp(&m_distance, m_distanceMin, m_distanceMax);
		return false;
	}

}