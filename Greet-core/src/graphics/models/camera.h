#pragma once

#include <math\maths.h>
//#include <graphics/models/entitymodel.h>
//#include <graphics/renderers/renderer3d.h>

namespace greet { namespace model {
	class Camera {

	public:
		virtual const math::vec3& getRotationVector() const = 0;
		virtual const math::mat4& getViewMatrix() const = 0;
		virtual void update(float timeElapsed) {};
	};


}}