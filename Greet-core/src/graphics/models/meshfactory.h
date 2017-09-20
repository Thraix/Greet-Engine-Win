#pragma once

#include <graphics/models/meshdata.h>
#include <math\maths.h>

namespace greet { namespace model { namespace MeshFactory {
	math::vec3 calculateNormal(math::vec3 p1, math::vec3 p2, math::vec3 p3);
	void calculateNormals(math::vec3* vertices, uint vertexCount, uint* indices, uint indexCount, math::vec3* normals);
	math::vec3* calculateNormals(math::vec3* vertices, uint vertexCount, uint* indices, uint indexCount);
	MeshData* quad(float x, float y, float z, float width, float length);
	MeshData* cube(float x, float y, float z, float width, float height, float length);
	MeshData* tetrahedron(float x, float y, float z, float size);
	MeshData* grid(float x, float y, float z, float width, float length, uint gridWidth, uint gridLength, float* heightMap, float height);
	MeshData* grid(float x, float y, float z, float width, float length, uint gridWidth, uint gridLength);
}}}