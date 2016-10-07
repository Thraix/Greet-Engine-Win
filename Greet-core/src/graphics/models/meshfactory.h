#pragma once

#include <graphics/models/mesh.h>

namespace greet { namespace model { namespace MeshFactory {
	Mesh* quad(float x, float y, float z, float width, float length);
	Mesh* cube(float x, float y, float z, float width, float height, float length);
	Mesh* tetrahedron(float x, float y, float z, float size);
	Mesh* grid(float x, float y, float z, float width, float length, uint gridWidth, uint gridLength, float* heightMap, float height);
}}}