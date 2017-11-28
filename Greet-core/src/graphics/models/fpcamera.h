#include "Camera.h"

namespace Greet {

	class FPCamera : public Camera
	{
	public:
		vec3 position;
		float yaw;
		float pitch;
		float roll;

		const vec3& getRotationVector() const { return vec3(yaw,pitch,roll); }
		const mat4& getViewMatrix() const { return mat4::viewMatrix(position, getRotationVector()); }

	};
}