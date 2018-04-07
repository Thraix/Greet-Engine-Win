#include "ModelExport.h"

#include "Grid.h"

namespace vmc
{
	using namespace Greet;

	std::pair<Vec3, Vec3> ModelExport::GetAllSquares(const std::set<Cube, CubeCompare>& cubes)
	{
		std::pair<Vec4, Vec4> squares;
 		bool* grid = new bool[Grid::GRID_SIZE*Grid::GRID_SIZE];
		uint minX, maxX, minY, maxY, minZ, maxZ;

		CalculateBoundingBox(cubes, &minX,&maxX, &minY,&maxY,&minZ,&maxZ);

		uint diffX = maxX - minX;
		uint diffY = maxY - minY;
		uint diffZ = maxZ - minZ;
		std::unordered_map<uint, bool*> colorMaps;

		std::deque<bool*> buffersX;
		std::deque<bool*> buffersY;
		std::deque<bool*> buffersZ;

		// Current layer
		for (uint x = minX; x <= maxX; ++x)
		{
			// Go through each cube in layer
			for (uint y = minY; y < maxY; ++y)
			{
				for (uint z = minZ; z < maxZ; ++z)
				{
					auto cube = cubes.find(Cube::Hash(x, y, z));

					if (cube != cubes.end()) 
					{
						// Determain if the cube side will be visible
						if (!Cube::ValidPos(x - 1) || cubes.count(Cube::Hash(x - 1, y, z)) == 0)
						{
							AddCubeXNegSideToMap(*cube, diffY, diffZ, &colorMaps, &buffersX);
						}
					}
				}
			}

			// Now we have 2d maps of all the color layers in colorMaps.
			for (auto mapIt = colorMaps.begin(); mapIt != colorMaps.end(); ++mapIt)
			{
				// Save to file or smth to check if it works.
			}

			// Move all color maps to the deque.
			auto mapIt = colorMaps.begin();
			while (mapIt != colorMaps.end())
			{
				auto it = mapIt;
				++mapIt;

				buffersX.push_back(it->second);
				colorMaps.erase(mapIt);
			}
		}
		return std::pair<Vec3, Vec3>();
	}

	// See if we can make this general for both directions and x,y,z otherwise copy paste code.
	void ModelExport::AddCubeXNegSideToMap(const Cube& cube, uint diffY, uint diffZ, std::unordered_map<uint, bool*>* colorMaps, std::deque<bool*>* buffers)
	{
		// Check if we already have a map with a certain color
		auto colorMap = colorMaps->find(cube.color);
		if (colorMap != colorMaps->end())
		{
			colorMap->second[cube.x + cube.y * diffY] = true;
		}
		else // Otherwise add the buffer to the colorMap
		{
			// Check if we need to create a buffer.
			if (buffers->size() == 0)
			{
				bool* buffer = GenBuffer(diffY, diffZ);

				// Clear memory in case of clutter
				memset(buffer, 0, diffY * diffZ);
				buffer[cube.x + cube.y * diffY] = true;
				colorMaps->emplace(cube.color, buffer);
			}
			else // Otherwise use an existing one.
			{
				// Get a stored buffer
				bool* buffer = *buffers->begin();
				buffer[cube.x + cube.y * diffY] = true;
				colorMaps->emplace(cube.color, buffer);

				// remove from available buffers
				buffers->pop_back();
			}
		}
	}

	// Generate a buffer with size width*height
	bool* ModelExport::GenBuffer(uint width, uint height)
	{
		return new bool[width*height];
	}

	// Delete a generated buffer.
	void ModelExport::DeleteBuffer(bool* buffer)
	{
		if(buffer != NULL)
			delete[] buffer;
	}

	// Calculate the minimum bounding box that can fit the model.
	void ModelExport::CalculateBoundingBox(const std::set<Cube, CubeCompare>& cubes, uint* minX, uint* maxX, uint* minY, uint* maxY, uint* minZ, uint* maxZ)
	{
		auto it = cubes.begin();

		// Initialize the variables
		*minX = it->x;
		*maxX = it->x;
		*minY = it->y;
		*maxY = it->y;
		*minZ = it->z;
		*maxZ = it->z;

		++it;

		for (; it != cubes.end(); ++it)
		{
			if (it->x < *minX)
				*minX = it->x;
			else if (it->x > *maxX) // variable cannot be min and max at the same time.
				*maxX = it->x;

			if (it->y < *minY)
				*minY = it->y;
			else if (it->y > *maxY) // variable cannot be min and max at the same time.
				*maxY = it->y;

			if (it->z < *minZ)
				*minX = it->z;
			else if (it->z > *maxZ) // variable cannot be min and max at the same time.
				*maxZ = it->z;
		}
	}
}