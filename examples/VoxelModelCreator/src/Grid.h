#pragma once

#include <set>
#include <greet.h>
#include "Cube.h"

#define VMC_GRID_SIZE 100

#include "GridRenderer3D.h"
#include "Cube.h"

namespace vmc {
	class Grid
	{
	private:
		GridRenderer3D renderer;
		std::set<Cube> m_grid;

	public:
		Grid();

		void Update(float timeElapsed);
		// Render the grid
		void Render();

		void Remove(uint x, uint y, uint z);
		void Remove(const Cube& cube);
		void Add(uint x, uint y, uint z, uint color);
		void Add(const Cube& cube);
	};
}