#include "Grid.h"
namespace vmc
{

	using namespace Greet;

	Grid::Grid()
		: renderer(Window::GetWidth(), Window::GetHeight(), new TPCamera(Vec3(VMC_GRID_SIZE / 2+0.5f, VMC_GRID_SIZE / 2 + 0.5f, VMC_GRID_SIZE / 2 + 0.5f), 15, 0, 0, 1, 80, -0.8, 0.8f), 90, 0.1, 1000.0f, new Skybox(TextureManager::Get3D("skybox"))),
		toolBox(this),
		m_color(0xffffffff)
	{
		EventDispatcher::AddKeyListener(DISPATCHER_GUI+2, *this);
		EventDispatcher::AddMouseListener(DISPATCHER_GUI + 2, *this);
		uint middle = VMC_GRID_SIZE / 2;
		Add(VMC_GRID_SIZE / 2, VMC_GRID_SIZE / 2, VMC_GRID_SIZE / 2, 0xffffffff);
		hasSelected = false;
		hasAdjacent = false;
	}

	bool Grid::OnPressed(const KeyPressedEvent& e)
	{
		return false;
	}

	bool Grid::OnPressed(const MousePressedEvent& e)
	{
		if (e.GetButton() == GLFW_MOUSE_BUTTON_1)
		{
			if (toolBox.OnLeftClick())
				return true;
		}
		if (e.GetButton() == GLFW_MOUSE_BUTTON_2)
		{
			if (toolBox.OnRightClick())
				return true;
		}

		renderAxis = true;

		return false;
	}

	bool Grid::OnReleased(const MouseReleasedEvent& e)
	{
		if (e.GetButton() == GLFW_MOUSE_BUTTON_1)
		{
			renderAxis = false;
		}
		return false;
	}

	void Grid::Update(float timeElapsed)
	{
		renderer.Update(timeElapsed);

		Vec3 near, direction;
		renderer.GetWorldCoordination(Window::GetMousePos(), &near, &direction);

		m_ray = Ray::GetCubeRay(near,direction, VMC_GRID_SIZE);
		auto lastIt = m_ray.begin();
		hasSelected = false;
		hasAdjacent = false;
		for (auto it = m_ray.begin(); it != m_ray.end(); ++it)
		{
			if (m_grid.count(*it))
			{
				hasAdjacent = (*it != *lastIt);
				hasSelected = true;

				selected = *it;
				adjacent = *lastIt;
				break;
			}
			lastIt = it;
		}
	}

	void Grid::Render()
	{
		renderer.Begin();

		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
		renderer.DrawCube(Vec3(-0.5f, -0.5f, -0.5f), Vec3(VMC_GRID_SIZE+1, VMC_GRID_SIZE + 1, VMC_GRID_SIZE + 1), 0xff000000, false);
		if (hasSelected)
		{
			float outline = 0.01f;
			renderer.DrawCube(selected.GetPosition() - outline, Vec3(1.0f, 1.0f, 1.0f) + outline * 2, 0xff000000, true);
		}
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

		for (auto it = m_grid.begin(); it != m_grid.end(); ++it)
		{
			renderer.Submit(*it);
		}

		if (renderAxis)
		{
			const TPCamera& cam = (const TPCamera&)renderer.GetCamera();
			Vec3 pos = cam.GetPosition();
			renderer.DrawLine(pos, pos + Vec3(10, 0, 0), Vec4(1, 0, 0, 1));
			renderer.DrawLine(pos, pos + Vec3(0, 10, 0), Vec4(0, 1, 0, 1));
			renderer.DrawLine(pos, pos + Vec3(0, 0, 10), Vec4(0, 0, 1, 1));
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

	void Grid::Add(Cube cube)
	{
		if (m_grid.count(cube))
		{
			Greet::Log::Error("Cube already exists");
			return;
		}
		cube.color = m_color;
		m_grid.emplace(cube);
	}
}