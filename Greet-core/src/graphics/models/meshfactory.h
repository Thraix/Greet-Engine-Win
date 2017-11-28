#pragma once

#include <graphics/models/MeshData.h>
#include <math/Maths.h>

namespace Greet { namespace MeshFactory {
	vec3 calculateNormal(vec3 p1, vec3 p2, vec3 p3);
	void calculateNormals(vec3* vertices, uint vertexCount, uint* indices, uint indexCount, vec3* normals);
	vec3* calculateNormals(vec3* vertices, uint vertexCount, uint* indices, uint indexCount);
	MeshData* quad(float x, float y, float z, float width, float length);
	MeshData* cube(float x, float y, float z, float width, float height, float length);
	MeshData* tetrahedron(float x, float y, float z, float size);
	MeshData* grid(float x, float y, float z, float width, float length, uint gridWidth, uint gridLength, float* heightMap, float height);
	uint indexGrid(uint x, uint z, uint gridWidth, uint gridLength);
	MeshData* lowPolyGrid(float x, float y, float z, float width, float length, uint gridWidth, uint gridLength, float* heightMap, float height);
	MeshData* grid(float x, float y, float z, float width, float length, uint gridWidth, uint gridLength);
}}