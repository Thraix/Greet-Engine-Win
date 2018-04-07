#include "Grid.h"
namespace vmc
{

	using namespace Greet;

	const uint Grid::GRID_SIZE = 100;

	Grid::Grid(ColorPicker* colorPicker)
		: renderer(Window::GetWidth(), Window::GetHeight(), new TPCamera(Vec3(GRID_SIZE / 2+0.5f, GRID_SIZE / 2 + 0.5f, GRID_SIZE / 2 + 0.5f), 15, 0, 0, 1, 80, -0.8, 0.8f), 90, 0.1, 1000.0f, new Skybox(TextureManager::Get3D("skybox"))),
		toolBox(this),
		m_colorPicker(colorPicker)

	{
		EventDispatcher::AddKeyListener(1, *this);
		EventDispatcher::AddMouseListener(1, *this);
		uint middle = GRID_SIZE / 2;
		Add(GRID_SIZE / 2, GRID_SIZE / 2, GRID_SIZE / 2, 0xffffffff);
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

		m_ray = Ray::GetCubeRay(near,direction, GRID_SIZE);
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
		renderer.DrawCube(Vec3(-0.5f, -0.5f, -0.5f), Vec3(GRID_SIZE +1, GRID_SIZE + 1, GRID_SIZE + 1), 0xff000000, false);
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
		Add(Cube(x, y, z, color),false);
	}

	void Grid::Add(Cube cube, bool setColor)
	{
		if (m_grid.count(cube))
		{
			Greet::Log::Error("Cube already exists");
			return;
		}
		if(setColor)
			cube.color = ColorUtils::Vec4ToColorHex(ColorUtils::HSVtoRGB(m_colorPicker->GetColor()));
		m_grid.emplace(cube);
	}

	void Grid::SaveModel(const std::string& filename)
	{
		JSONArray jsonArray;
		for (auto it = m_grid.begin();it != m_grid.end();++it)
		{
			Vec3 position = it->GetPosition();
			JSONObject cubeObj;
			cubeObj.AddValue("x", std::to_string((uint)position.x));
			cubeObj.AddValue("y", std::to_string((uint)position.y));
			cubeObj.AddValue("z", std::to_string((uint)position.z));
			cubeObj.AddValue("color", std::to_string(it->color));
			jsonArray.AddObject(cubeObj);
		}
		std::fstream file(filename, std::fstream::out);
		JSONObject obj;
		obj.AddArray("cubes", jsonArray);
		file << obj;
		file.close();
	}

	void Grid::LoadModel(const std::string& filename)
	{
		m_grid.clear();
		JSONObject obj = JSONLoader::LoadJSON(filename);
		JSONArray cubes = obj.GetArray("cubes");
		for (uint i = 0;i < cubes.Size(); ++i)
		{
			JSONObject cube = cubes[i];
			Add(cube.GetValueAsUint("x"), cube.GetValueAsUint("y"), cube.GetValueAsUint("z"), cube.GetValueAsUint("color"));
		}

	}


	void Grid::ExportModel(const std::string& filename)
	{
		// TODO: Turn the voxels into actual models.
	}
}