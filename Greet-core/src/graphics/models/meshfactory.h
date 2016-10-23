#pragma once

#include <graphics/models/meshdata.h>
#include <math\maths.h>

namespace greet { namespace model { namespace MeshFactory {
	MeshData* quad(float x, float y, float z, float width, float length);
	MeshData* cube(float x, float y, float z, float width, float height, float length);
	MeshData* tetrahedron(float x, float y, float z, float size);
	MeshData* grid(float x, float y, float z, float width, float length, uint gridWidth, uint gridLength, float* heightMap, float height);
	MeshData* grid(float x, float y, float z, float width, float length, uint gridWidth, uint gridLength);
}}}