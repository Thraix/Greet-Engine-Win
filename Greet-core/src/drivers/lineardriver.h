#pragma once

#include <drivers\driver1.h>

namespace greet {
	namespace drivers {

		class LinearDriver : public Driver1
		{
		public:
			float m_speed;
		public:

			LinearDriver(float& value, float change, float time, bool relativeChange, DriverListener* listener);
			void update() override;
		};

	}
}
