#pragma once

#include <math\maths.h>
//#include <graphics/models/entitymodel.h>
//#include <graphics/renderers/renderer3d.h>

namespace Greet {
	class Camera {

	public:
		virtual const vec3& getRotationVector() const = 0;
		virtual const mat4& getViewMatrix() const = 0;
		virtual void update(float timeElapsed) {};
	};


}