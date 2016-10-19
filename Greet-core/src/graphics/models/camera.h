#pragma once

#include <math\maths.h>
//#include <graphics/models/entitymodel.h>
//#include <graphics/renderers/renderer3d.h>

namespace greet { namespace model {
	class Camera {

	public:
		math::vec3 position;
		float pitch = 0;
		float yaw = 0;
		float roll = 0;

	public:
		Camera(math::vec3 position);
		inline math::vec3 getRotationVector() const { return math::vec3(pitch, yaw, roll); }
		inline math::mat4 getViewMatrix() const { return math::mat4::viewMatrix(position, math::vec3(pitch, yaw, roll)); }
		//inline math::vec3 getPosition() const { return m_position; }
		//inline float getPitch() const { return m_pitch; }
		//inline float getYaw() const { return m_yaw; }
		//inline float getRoll() const { return m_roll; }


	};


}}