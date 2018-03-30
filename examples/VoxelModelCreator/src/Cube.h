#pragma once

#include <greet.h>

namespace vmc
{

	class Cube
	{
	private:
		uint x;
		uint y;
		uint z;
	public:
		uint color;
	public:
		Cube(uint x, uint y, uint z, uint color)
			: x(x), y(y), z(z), color(color)
		{
			if (x < 0 || x >= 1000)
				Greet::Log::Error("Cube x position out of bounds (0-999): ", x);
			if(y < 0 || y >= 1000)
				Greet::Log::Error("Cube x position out of bounds (0-999): ", x);
			if(z < 0 || z >= 1000)
				Greet::Log::Error("Cube x position out of bounds (0-999): ", x);
		}

		Greet::Vec3 GetPosition() const
		{
			return Greet::Vec3(x, y, z);
		}

		// Only Allowes 1000 x 1000 x 1000 grids.
		static uint hash(uint x, uint y, uint z)
		{
			return x + y * 1000 + z * 1000 * 1000;
		}

		static uint hash(const Cube& cube)
		{
			return cube.x + cube.y * 1000 + cube.z * 1000 * 1000;
		}

		friend bool operator<(const Cube& c1, const Cube& c2)
		{
			return hash(c1) < hash(c2);
		}
	};
}