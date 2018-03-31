#pragma once

#include <set>
#include <greet.h>
#include "Cube.h"

#define VMC_GRID_SIZE 100

#include "GridRenderer3D.h"
#include "Cube.h"

namespace vmc {
	class Grid : public Greet::KeyListener, public Greet::MouseListener
	{
	private:
		GridRenderer3D renderer;
		std::set<Cube> m_grid;
		std::vector<Cube> m_ray;
		bool hasAdjacent;
		bool hasSelected;
		Cube selected;
		Cube adjacent;

		bool renderAxis;

	private:
		float GetIntersectionT(float plane, float near, float invDirection) const;
		bool RayInside(float plane1, float plane2, float min1, float max1, float min2, float max2) const;
	public:
		Grid();

		std::vector<Cube> GetCubeRay() const;

		bool OnPressed(const Greet::KeyPressedEvent& e) override;
		bool OnPressed(const Greet::MousePressedEvent& e) override;
		bool OnReleased(const Greet::MouseReleasedEvent& e) override;

		void Update(float timeElapsed);
		// Render the grid
		void Render();

		void Remove(uint x, uint y, uint z);
		void Remove(const Cube& cube);
		void Add(uint x, uint y, uint z, uint color);
		void Add(const Cube& cube);
	};
}