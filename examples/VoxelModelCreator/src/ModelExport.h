#pragma once

#include <math/Vec4.h>
#include <utility>
#include <set>

#include "Cube.h"
namespace vmc
{

	enum Layer
	{
		XNeg, XPos, YNeg, YPos, ZNeg, ZPos
	};

	class ModelExport {
	private:

	public:
		static std::pair<Greet::Vec3, Greet::Vec3> GetAllSquares(const std::set<Cube, CubeCompare>& cubes);

	private:

		static void AddCubeXNegSideToMap(const Cube& cube, uint diffX, uint diffY, std::map<uint, bool*>* colorMaps, std::deque<bool*>* buffers);

		static bool* GenBuffer(uint width, uint height);
		static void DeleteBuffer(bool* buffer);
		static void CalculateBoundingBox(const std::set<Cube, CubeCompare>& m_grid, uint* minX, uint* maxX, uint* minY, uint* maxY, uint* minZ, uint* maxZ);
	};

}