#include "camera.h"
#include <math/maths.h>
#include <event/mouselistener.h>
#include <internal/greetgl.h>
#include <event/eventdispatcher.h>

namespace greet { namespace model {

	class TPCamera : public Camera, public event::MouseListener
	{
	private:
		bool m_mouse1 = false;
		bool m_mouse3 = false;

		// Clamps to the camera position
		float m_distanceMin;
		float m_distanceMax;
		float m_heightMin;
		float m_heightMax;

		// Speed of the camera
		float m_rotationSpeed;
		float m_heightSpeed;
		float m_distanceSpeed;

		math::vec3 m_position;
		float m_distance;
		float m_height;
		float m_rotation;
		float m_rotationWanted;

		// Calculated information
		math::mat4 m_viewMatrix;
		math::vec3 m_rotationVector;
	private:
		void calculateRotationVector();
		void calculateViewMatrix();
		void calculateInformation();
	public:
		TPCamera();
		TPCamera(math::vec3 position, float distance, float height, float rotation);
		TPCamera(math::vec3 position, float distance, float height, float rotation, float distanceMin, float distanceMax, float heightMin, float heightMax);
		TPCamera(math::vec3 position, float distance, float height, float rotation, float distanceMin, float distanceMax, float heightMin, float heightMax, float rotationSpeed, float heightSpeed, float distanceSpeed);
		virtual ~TPCamera();

		const math::vec3& getRotationVector() const override;
		const math::mat4& getViewMatrix() const override;
		void update(float timeElapsed) override;

		float getHeight() const { return m_height; }
		float getRotation() const { return m_rotation; }
		float getDistance() const { return m_distance; }

		void setPosition(math::vec3 pos);
		void setHeight(float height);
		void setRotation(float rotation);
		void setDistance(float distance);
		void setDistanceClamp(float min, float max);
		void setHeightClamp(float min, float max);

		bool onMoved(const event::MouseMovedEvent& e) override;
		bool onPressed(const event::MousePressedEvent& e) override;
		bool onReleased(const event::MouseReleasedEvent& e) override;
		bool onScroll(const event::MouseScrollEvent& e) override;
	};

}}