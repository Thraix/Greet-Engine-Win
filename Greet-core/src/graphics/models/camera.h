#pragma once

#include <math/Maths.h>
//#include <graphics/models/EntityModel.h>
//#include <graphics/renderers/Renderer3D.h>

namespace Greet {
	class Camera {

	public:
		virtual const vec3& getRotationVector() const = 0;
		virtual const mat4& getViewMatrix() const = 0;
		virtual void update(float timeElapsed) {};
	};


}