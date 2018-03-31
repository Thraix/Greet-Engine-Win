#include "Grid.h"
namespace vmc
{

	using namespace Greet;

	Grid::Grid()
		: renderer(Window::GetWidth(), Window::GetHeight(), new TPCamera(Vec3(0, 0, 0), 15, 0, 0, 1, 80, -0.8, 0.8f), 90, 0.1, 1000.0f, new Skybox(TextureManager::Get3D("skybox")))
	{
		EventDispatcher::AddKeyListener(0, *this);
		uint middle = VMC_GRID_SIZE / 2;
		Add(0,0,0, 0xffffffff);
		Add(0, 1, 0, 0xffff00ff);
		Add(0, 1, 1, 0xff00ffff);
		Add(1, 0, 0, 0xffffff00);
	}

	bool Grid::OnPressed(const KeyPressedEvent& e)
	{
		return false;
	}

	std::vector<Cube> Grid::GetCubeRay() const
	{
		Vec3 near, direction;
		renderer.GetWorldCoordination(Window::GetMousePos(), &near, &direction);
		Vec3 invDirection = Vec3(1.0f / direction.x, 1.0f / direction.y, 1.0f / direction.z);
		std::vector<Cube> cubes;

		int x = floor(near.x);
		int y = floor(near.y);
		int z = floor(near.z);

		// If the near position is outside the work area, recalc position.
		if (near.x < 0 || near.x > VMC_GRID_SIZE || near.y < 0 || near.y > VMC_GRID_SIZE || near.z < 0 || near.z > VMC_GRID_SIZE)
		{
			// These will not give any cubes since we are "aiming" outside the box.
			if (near.x < 0 && direction.x <= 0)
				return cubes;
			if (near.y < 0 && direction.y <= 0)
				return cubes;
			if (near.z < 0 && direction.z <= 0)
				return cubes;
			if (near.x > 100 && direction.x >= 0)
				return cubes;
			if (near.y > 100 && direction.y >= 0)
				return cubes;
			if (near.z > 100 && direction.z >= 0)
				return cubes;

			// Calculate the t values for the plane intersections.
			//
			float tX = GetIntersectionT(near.x < 0 ? 0 : VMC_GRID_SIZE, near.x, invDirection.x);
			float tY = GetIntersectionT(near.y < 0 ? 0 : VMC_GRID_SIZE, near.y, invDirection.y);
			float tZ = GetIntersectionT(near.z < 0 ? 0 : VMC_GRID_SIZE, near.z, invDirection.z);

			// If x is outside, check if the tX value will intersect with the work area.
			if ((near.x < 0 || near.x > 100) && RayInside(near.y + tX*direction.y, near.z + tX*direction.z, 0, VMC_GRID_SIZE, 0, VMC_GRID_SIZE))
			{
				near += direction * tX;
				near.x = round(near.x);
				x = direction.x < 0 ? VMC_GRID_SIZE : 0;
				y = floor(near.y);
				z = floor(near.z);
			}
			// If y is outside, check if the tY value will intersect with the work area.
			else if ((near.y < 0 || near.y > 100) && RayInside(near.x + tY*direction.x, near.z + tY*direction.z, 0, VMC_GRID_SIZE, 0, VMC_GRID_SIZE))
			{
				near += direction * tY;
				near.y = round(near.y);
				y = direction.y < 0 ? VMC_GRID_SIZE : 0;
				x = floor(near.x);
				z = floor(near.z);
			}
			// If z is outside, check if the tZ value will intersect with the work area.
			else if ((near.z < 0 || near.z > 100) && RayInside(near.x + tZ*direction.x, near.y + tZ*direction.y, 0, VMC_GRID_SIZE, 0, VMC_GRID_SIZE))
			{
				near += direction * tZ;
				near.z = round(near.z);
				z = direction.z < 0 ? VMC_GRID_SIZE : 0;
				x = floor(near.x);
				y = floor(near.y);
			}
			// If none intersects with the work area there are no cubes that are ray traced.
			else
			{
				return cubes;
			}
			
		}

		// near is now clipping the work area in some way.
		//Vec3 pos = near;

		int dX = direction.x < 0 ? -1 : 1;
		int dY = direction.y < 0 ? -1 : 1;
		int dZ = direction.z < 0 ? -1 : 1;

		float tDeltaX = GetIntersectionT(dX, 0, invDirection.x);
		float tDeltaY = GetIntersectionT(dY, 0, invDirection.y);
		float tDeltaZ = GetIntersectionT(dZ, 0, invDirection.z);

		float tX = GetIntersectionT(direction.x < 0 ? floor(near.x - 0.0001f) : ceil(near.x+0.0001f), near.x, invDirection.x);
		float tY = GetIntersectionT(direction.y < 0 ? floor(near.y - 0.0001f) : ceil(near.y + 0.0001f), near.y, invDirection.y);
		float tZ = GetIntersectionT(direction.z < 0 ? floor(near.z - 0.0001f) : ceil(near.z + 0.0001f), near.z, invDirection.z);

		uint i = 1;
		while (true)
		{
			cubes.push_back(Cube(x, y, z, 0xff000000 | (rand() % 255) << 16 | (rand() % 255) << 8 | (rand() % 255)));
			float minT = std::min(abs(tX), std::min(abs(tY), abs(tZ)));
			if (abs(tX) == minT)
			{
				x += dX;
				if (x < 0 || x >= VMC_GRID_SIZE)
					break;
				tX += tDeltaX;
			}
			else if (abs(tY) == minT)
			{
				y += dY;
				if (y < 0 || y >= VMC_GRID_SIZE)
					break;
				tY += tDeltaY;
			}
			else // if(abs(tZ) == minT)
			{
				z += dZ;
				if (z < 0 || z >= VMC_GRID_SIZE)
					break;
				tZ += tDeltaZ;
			}
		}

		return cubes;
	}

	bool Grid::RayInside(float plane1, float plane2, float min1, float max1, float min2, float max2) const
	{
		return plane1 >= min1 && plane1 < max1 && plane2 >= min2 && plane2 < max2;
	}

	float Grid::GetIntersectionT(float planePos, float start, float invDirection) const
	{
		return (planePos - start) * invDirection;
	}

	void Grid::Update(float timeElapsed)
	{
		m_ray = GetCubeRay();
		renderer.Update(timeElapsed);
	}

	void Grid::Render()
	{
		renderer.Begin();
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
		renderer.DrawCube(Vec3(-0.5f, -0.5f, -0.5f), Vec3(VMC_GRID_SIZE+1, VMC_GRID_SIZE + 1, VMC_GRID_SIZE + 1), 0xff000000, false);
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

		for (auto it = m_grid.begin(); it != m_grid.end(); ++it)
		{
			renderer.Submit(*it);
		}

		uint i = 0;
		for (auto it = m_ray.begin(); it != m_ray.end(); ++it)
		{
			if (m_grid.count(*it))
			{
				const Cube& cube = *it;
				GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
				float outline = 0.01f;
				renderer.DrawCube(cube.GetPosition()- outline, Vec3(1.0f,1.0f,1.0f)+ outline*2, 0xff000000, true);
				GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
				break;
			}
			i++;
		}

		const TPCamera& cam = (const TPCamera&)renderer.GetCamera();
		Vec3 pos = cam.GetPosition();
		renderer.DrawLine(pos, pos + Vec3(10, 0, 0), Vec4(1, 0, 0, 1));
		renderer.DrawLine(pos, pos + Vec3(0, 10, 0), Vec4(0, 1, 0, 1));
		renderer.DrawLine(pos, pos + Vec3(0, 0, 10), Vec4(0, 0, 1,1));
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