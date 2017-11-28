#pragma once

#include <graphics/models/MeshData.h>
#include <math/Maths.h>

namespace Greet {
	class MeshFactory
	{
		public:
			static Vec3 CalculateNormal(Vec3 p1, Vec3 p2, Vec3 p3);
			static void CalculateNormals(Vec3* vertices, uint vertexCount, uint* indices, uint indexCount, Vec3* normals);
			static Vec3* CalculateNormals(Vec3* vertices, uint vertexCount, uint* indices, uint indexCount);
			static MeshData* Quad(float x, float y, float z, float width, float length);
			static MeshData* Cube(float x, float y, float z, float width, float height, float length);
			static MeshData* Tetrahedron(float x, float y, float z, float size);
			static MeshData* Grid(float x, float y, float z, float width, float length, uint gridWidth, uint gridLength, float* heightMap, float height);
			static uint IndexGrid(uint x, uint z, uint gridWidth, uint gridLength);
			static MeshData* LowPolyGrid(float x, float y, float z, float width, float length, uint gridWidth, uint gridLength, float* heightMap, float height);
			static MeshData* Grid(float x, float y, float z, float width, float length, uint gridWidth, uint gridLength);
	};
}