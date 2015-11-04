#pragma once

#include <math\maths.h>

namespace greet { namespace physics{

	class Shape
	{
		public:

		protected:
			math::vec2 m_center;
			math::vec2 m_size;
		public:
			Shape(math::vec2 center, math::vec2 size);

			inline void move(math::vec2 move) { this->m_center += move; }
			inline void setPos(math::vec2 center) { this->m_center = center; }
			inline void setSize(math::vec2 size) { this->m_size = size; }
			inline const math::vec2& getPos() const { return m_center; }
			inline const math::vec2& getSize() const { return m_size; }
		protected:
	};
}}