#include "Grid.h"
namespace vmc
{

	using namespace Greet;

	Grid::Grid()
		: renderer(Window::GetWidth(), Window::GetHeight(), new TPCamera(Vec3(0, 0, 0), 15, 0, 0, 1, 80, -0.8, 0.8f), 90, 0.1, 1000.0f, new Skybox(TextureManager::Get3D("skybox")))
	{

		uint middle = VMC_GRID_SIZE / 2;
		Add(0,0,0, 0xffffffff);
		Add(0, 1, 0, 0xffff00ff);
		Add(0, 1, 1, 0xff00ffff);
		Add(1, 0, 0, 0xffffff00);
	}

	void Grid::Update(float timeElapsed)
	{
		renderer.Update(timeElapsed);
	}

	void Grid::Render()
	{
		renderer.Begin();
		
		for (auto it = m_grid.begin(); it != m_grid.end(); ++it)
		{
			renderer.Submit(*it);
		}

		renderer.End();
	}

	void Grid::Remove(uint x, uint y, uint z)
	{
		Remove(Cube(x, y, z, 0x00000000));
	}

	void Grid::Remove(const Cube& cube)
	{
		m_grid.erase(cube);
	}

	void Grid::Add(uint x, uint y, uint z, uint color)
	{
		Add(Cube(x, y, z, color));
	}

	void Grid::Add(const Cube& cube)
	{
		if (m_grid.count(cube))
		{
			Greet::Log::Error("Cube already exists");
			return;
		}
		m_grid.emplace(cube);
	}
}