#include "camera.h"

namespace greet { namespace model {

	class TPCamera : public Camera
	{
	public:
		math::vec3 position;
		float distance;
		float height; // -1 to 1
		float rotation;

		math::vec3 getRotationVector() const { return math::vec3(0, 0, 0); }
		math::mat4 getViewMatrix() const { return math::mat4::tpCamera(position, distance, height, rotation); }
	};

}}