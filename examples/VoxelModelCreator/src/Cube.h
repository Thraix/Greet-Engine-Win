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
			if (x >= 1000)
				Greet::Log::Error("Cube x position out of bounds (0-999): ", x);
			if(y >= 1000)
				Greet::Log::Error("Cube y position out of bounds (0-999): ", y);
			if(z >= 1000)
				Greet::Log::Error("Cube z position out of bounds (0-999): ", z);
		}

		Cube(uint x, uint y, uint z)
			: Cube(x, y, z, 0xffffffff)
		{

		}

		Cube()
			: Cube(0, 0, 0, 0xffffffff)
		{

		}

		Greet::Vec3 GetPosition() const
		{
			return Greet::Vec3(x, y, z);
		}

		void clone(const Cube& cube)
		{
			x = cube.x;
			y = cube.y;
			z = cube.z;
			color = cube.color;
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

		friend bool operator==(const Cube& c1, const Cube& c2)
		{
			return hash(c1) == hash(c2);
		}

		friend bool operator!=(const Cube& c1, const Cube& c2)
		{
			return hash(c1) != hash(c2);
		}
	};
}