#include "camera.h"

namespace greet { namespace model {

	class FPCamera : public Camera
	{
	public:
		math::vec3 position;
		float yaw;
		float pitch;
		float roll;

		math::vec3 getRotationVector() const { return math::vec3(yaw,pitch,roll); }
		math::mat4 getViewMatrix() const { return math::mat4::viewMatrix(position, getRotationVector()); }

	};
} }