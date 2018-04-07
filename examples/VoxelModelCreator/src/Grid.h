#pragma once

#include <set>
#include <greet.h>
#include "Cube.h"

#define VMC_GRID_SIZE 100

#include "GridRenderer3D.h"
#include "Cube.h"
#include "Ray.h"
#include "tools/ToolBox.h"
#include <sstream>

namespace vmc {
	class Grid : public Greet::KeyListener, public Greet::MouseListener
	{
	private:
		GridRenderer3D renderer;
		Greet::ColorPicker* m_colorPicker;
		std::set<Cube> m_grid;
		std::vector<Cube> m_ray;
		uint m_color;

		ToolBox toolBox;

		bool hasAdjacent;
		bool hasSelected;
		Cube selected;
		Cube adjacent;

		bool renderAxis;

	public:
		Grid(Greet::ColorPicker* colorPicker);

		bool OnPressed(const Greet::KeyPressedEvent& e) override;
		bool OnPressed(const Greet::MousePressedEvent& e) override;
		bool OnReleased(const Greet::MouseReleasedEvent& e) override;

		void Update(float timeElapsed);
		// Render the grid
		void Render();

		void Remove(uint x, uint y, uint z);
		void Remove(const Cube& cube);
		void Add(uint x, uint y, uint z, uint color);
		void Add(Cube cube, bool setColor=false);


		uint GetColor() const { return m_color; }
		void SetColor(uint color) { m_color = color; }
		GridRenderer3D* GetRenderer() { return &renderer; }

		bool HasAdjacent() const { return hasAdjacent; }
		bool HasSelected() const { return hasSelected; }
		const Cube& GetAdjacentCube() const { return adjacent; }
		const Cube& GetSelectedCube() const { return selected; }

		void SaveModel(const std::string& filename);
		void LoadModel(const std::string& filename);
		void ExportModel(const std::string& filename);

	};
}