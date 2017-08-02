#include "camera.h"

namespace greet { namespace model {

	class FPCamera : public Camera
	{
	public:
		math::vec3 position;
		float yaw;
		float pitch;
		float roll;

		const math::vec3& getRotationVector() const { return math::vec3(yaw,pitch,roll); }
		const math::mat4& getViewMatrix() const { return math::mat4::viewMatrix(position, getRotationVector()); }

	};
} }