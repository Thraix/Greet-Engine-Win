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
		float m_distanceMin = 1;
		float m_distanceMax = 100;
		float m_heightMin = -1;
		float m_heightMax = 1;

		// Speed of the camera
		float m_rotationSpeed = 0.5f;
		float m_heightSpeed = 0.01f;
		float m_distanceSpeed = 0.005f;

		math::vec3 m_position;
		float m_distance;
		float m_height;
		float m_rotation;

		// Calculated information
		math::mat4 m_viewMatrix;
		math::vec3 m_rotationVector;
	private:
		void calculateRotationVector();
		void calculateViewMatrix();
		void calculateInformation();
	public:
		TPCamera();
		virtual ~TPCamera();

		math::vec3 getRotationVector() const override;
		math::mat4 getViewMatrix() const override;



		bool onMoved(const event::MouseMovedEvent& e) override;
		bool onPressed(const event::MousePressedEvent& e) override;
		bool onReleased(const event::MouseReleasedEvent& e) override;
		bool onScroll(const event::MouseScrollEvent& e) override;


		void setDistanceClamp(float min, float max);
		void setHeightClamp(float min, float max);
		void setPosition(math::vec3 pos);
	};

}}