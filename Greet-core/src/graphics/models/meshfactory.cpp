#include "MeshFactory.h"
#include <logging/Log.h>
namespace Greet {
	
	// Calculate a normal of 3 points in space
	Vec3 MeshFactory::CalculateNormal(Vec3 p1, Vec3 p2, Vec3 p3)
	{
		Vec3 v1 = p2 - p1;
		Vec3 v2 = p3 - p1;
		Vec3 normal = v1.Cross(v2);
		return normal;
	}

	void MeshFactory::CalculateNormals(Vec3* vertices, uint vertexCount, uint* indices, uint indexCount, Vec3* normals)
	{
		Vec3 faceNormal;
		Vec3 p1, p2, p3;
		memset(normals, 0, sizeof(float) * 3 * vertexCount);
		for (int i = 0; i < indexCount; i += 3)
		{
			p1 = vertices[indices[i]];
			p2 = vertices[indices[i + 1]];
			p3 = vertices[indices[i + 2]];
			faceNormal = CalculateNormal(p1, p2, p3);
			normals[indices[i]] += faceNormal;
			normals[indices[i + 1]] += faceNormal;
			normals[indices[i + 2]] += faceNormal;
		}
		for (int i = 0; i < vertexCount; i++)
		{
			((Vec3*)normals)[i].Normalize();
		}
	}

	// Calculate normals for a mesh
	Vec3* MeshFactory::CalculateNormals(Vec3* vertices, uint vertexCount, uint* indices, uint indexCount)
	{
		Vec3* normals = new Vec3[vertexCount];
		CalculateNormals(vertices, vertexCount, indices, indexCount, normals);
		return normals;
	}

	MeshData* MeshFactory::Quad(float x, float y, float z, float width, float length)
	{
		Vec3 vertices[4];
		float halfWidth = width / 2.0f;
		float halfLength = length / 2.0f;
		vertices[0]  = Vec3(x-halfWidth, y, z-halfLength);
		vertices[1]  = Vec3(x+halfWidth, y, z-halfLength);
		vertices[2]  = Vec3(x+halfWidth, y, z+halfLength);
		vertices[3]  = Vec3(x-halfWidth, y, z+halfLength);

		Vec3 normals[4];	
		normals[0]  = Vec3(0.0f, 1.0f, 0.0f);
		normals[1]  = Vec3(0.0f, 1.0f, 0.0f);
		normals[2]  = Vec3(0.0f, 1.0f, 0.0f);
		normals[3]  = Vec3(0.0f, 1.0f, 0.0f);

		uint* indices = new uint[6]{0,1,2,0,2,3};
		MeshData* meshdata = new MeshData(vertices,4,indices,6);
		meshdata->AddAttribute(new AttributeData(ATTRIBUTE_NORMAL,normals));
		return meshdata;
	}
	// x, y, z
	MeshData* MeshFactory::Cube(float x, float y, float z, float width, float length, float height)
	{
		Vec3* vertices = new Vec3[8];
		float halfWidth = width / 2.0f;
		float halfLength = length / 2.0f;
		float halfHeight = height / 2.0f;
		vertices[0]  = Vec3(x-halfWidth, y-halfHeight, z-halfLength);
		vertices[1]  = Vec3(x-halfWidth, y+halfHeight, z-halfLength);
		vertices[2]  = Vec3(x-halfWidth, y+halfHeight, z+halfLength);
		vertices[3]  = Vec3(x-halfWidth, y-halfHeight, z+halfLength);

		vertices[4]  = Vec3(x+halfWidth, y-halfHeight, z-halfLength);
		vertices[5]  = Vec3(x+halfWidth, y+halfHeight, z-halfLength);
		vertices[6]  = Vec3(x+halfWidth, y+halfHeight, z+halfLength);
		vertices[7]  = Vec3(x+halfWidth, y-halfHeight, z+halfLength);

		float* normals = new float[8 * 3];
		((Vec3*)normals)[0] = Vec3(-1.0f, -1.0f, -1.0f);
		((Vec3*)normals)[1] = Vec3(-1.0f,  1.0f, -1.0f);
		((Vec3*)normals)[2] = Vec3(-1.0f,  1.0f,  1.0f);
		((Vec3*)normals)[3] = Vec3(-1.0f, -1.0f,  1.0f);
		((Vec3*)normals)[4] = Vec3( 1.0f, -1.0f, -1.0f);
		((Vec3*)normals)[5] = Vec3( 1.0f,  1.0f, -1.0f);
		((Vec3*)normals)[6] = Vec3( 1.0f,  1.0f,  1.0f);
		((Vec3*)normals)[7] = Vec3( 1.0f, -1.0f,  1.0f);
	
		uint* indices = new uint[36]{
			 0, 2, 1, 0, 3, 2,
			 3, 6, 2, 3, 7, 6,
			 7, 5, 6, 7, 4, 5,
			 4, 1, 5, 4, 0, 1,
			 2, 5, 1, 2, 6, 5,
			 3, 0, 4, 3, 4, 7 };

		MeshData* meshdata = new MeshData(vertices,8,indices,36);
		meshdata->AddAttribute(new AttributeData(ATTRIBUTE_NORMAL,normals));
		return meshdata;
	}

	MeshData* MeshFactory::Tetrahedron(float x, float y, float z, float size)
	{
		float tan30 = 0.5773502f;  //   tan(30/180*PI)
		float cos30 = 1.1547005f; //   1 / cos(30/180*PI) 
		float halfSize = size * 0.5f;
		float l1 = halfSize*cos30;
		float l2 = halfSize*tan30; // 
		float height = size*0.8164965f;// Height of tetrahedron
		float corner = size*0.4082483f; // size/sqrt(6) -> Center to corner
		float face = height - corner; // Center to face 

		Vec3 v1 = Vec3(x, y-face, z + l1);
		Vec3 v2 = Vec3(x + halfSize, y - face, z - l2);
		Vec3 v3 = Vec3(x - halfSize, y - face, z - l2);
		Vec3 v4 = Vec3(x, y + corner, z);


		Vec3* vertices = new Vec3[4];
		vertices[0] = v1;
		vertices[1] = v2;
		vertices[2] = v3;
		vertices[3] = v4;

		
		float* normals = new float[4 * 3];

		((Vec3*)normals)[0] = (v1 - Vec3(x, y, z)).Normalize();
		((Vec3*)normals)[1] = (v2 - Vec3(x, y, z)).Normalize();
		((Vec3*)normals)[2] = (v3 - Vec3(x, y, z)).Normalize();
		((Vec3*)normals)[3] = (v4 - Vec3(x, y, z)).Normalize();

		uint* indices = new uint[12]{ 0, 2, 1, 1, 3, 0, 2, 0, 3, 1, 2, 3};
		MeshData* meshdata = new MeshData(vertices, 4, indices, 12);
		meshdata->AddAttribute(new AttributeData(ATTRIBUTE_NORMAL,normals));
		return meshdata;
	}

	MeshData* MeshFactory::Grid(float x, float y, float z, float width, float length, uint gridWidth, uint gridLength)
	{
		return Grid(x,y,z,width,length,gridWidth,gridLength,NULL,0);
	}

	MeshData* MeshFactory::Grid(float x, float y, float z, float width, float length, uint gridWidth, uint gridLength, float* heightMap, float height)
	{
		if (gridWidth < 1 || gridLength < 1)
			return Quad(x, y, z, width, length);

		float tileWidth = width / (float)gridWidth;
		float tileLength = length / (float)gridLength;

		uint vertexCount = (gridWidth + 1) * (gridLength+ 1);

		Vec3* vertices = new Vec3[vertexCount];

		// decenter x and y
		x -= width / 2.0f;
		z -= length / 2.0f;


		for (uint iz = 0; iz <= gridLength; iz++)
		{
			for (uint ix = 0; ix <= gridWidth; ix++)
			{
				float heightM = heightMap == NULL ? 0 : heightMap[ix + iz*(gridWidth + 1)];
				vertices[ix + iz*(gridWidth + 1)] = Vec3(x + ix*tileWidth, y + heightM*height, z + iz*tileLength);
			}
		}

		uint indexCount = 6 * gridWidth * gridLength;
		uint* indices = new uint[indexCount];

		// Loop through every square
		uint i = 0;
		for (uint iz = 0; iz < gridLength; iz++)
		{
			for (uint ix = 0; ix < gridWidth; ix++)
			{
				if (ix % 2 == iz % 2)
				{
					indices[i++] = ix + iz * (gridWidth + 1);
					indices[i++] = ix + (iz + 1) * (gridWidth + 1);
					indices[i++] = ix + 1 + (iz + 1) * (gridWidth + 1);
					indices[i++] = ix + 1 + iz * (gridWidth + 1);
					indices[i++] = ix + iz * (gridWidth + 1);
					indices[i++] = ix + 1 + (iz + 1) * (gridWidth + 1);
				}
				else
				{
					indices[i++] = ix + iz * (gridWidth + 1);
					indices[i++] = ix + (iz + 1) * (gridWidth + 1);
					indices[i++] = ix + 1 + iz * (gridWidth + 1);
					indices[i++] = ix + 1 + iz * (gridWidth + 1);
					indices[i++] = ix + (iz + 1) * (gridWidth + 1);
					indices[i++] = ix + 1 + (iz + 1) * (gridWidth + 1);
				}
			}
		}

		Vec3* normals = CalculateNormals(vertices, vertexCount, indices, indexCount);
		MeshData* data = new MeshData(vertices, vertexCount, indices, indexCount);
		data->AddAttribute(new AttributeData(ATTRIBUTE_NORMAL, normals));

		return data;
	}

	uint MeshFactory::IndexGrid(uint x, uint z, uint gridWidth, uint gridLength)
	{
		if (z >= gridLength - 1)
		{
			return x + (z - (gridLength - 1)) * (gridWidth+1) + (gridLength - 1) * gridWidth * 2;
		}
		else if (x == 0)
		{
			return z * 2 * gridWidth;
		}
		else if (x == gridWidth)
		{
			return x * 2 - 1 + z * 2 * gridWidth;
		}
		else 
		{
			return x * 2 - 1 + z * 2 * gridWidth;
		}
		return 0;
	}

	MeshData* MeshFactory::LowPolyGrid(float x, float y, float z, float width, float length, uint gridWidth, uint gridLength, float* heightMap, float height)
	{
		if (gridWidth < 1 || gridLength < 1)
			return Quad(x, y, z, width, length);

		float tileWidth = width / (float)gridWidth;
		float tileLength = length / (float)gridLength;

		uint vertexCount = (gridWidth + 1) * (gridLength + 1) + (gridWidth - 1)*(gridLength - 1);

		Vec3* vertices = new Vec3[vertexCount];

		// decenter x and y
		x -= width / 2.0f;
		z -= length / 2.0f;

		for (uint iz = 0; iz <= gridLength; iz++)
		{
			for (uint ix = 0; ix <= gridWidth; ix++)
			{
				float heightM = heightMap == NULL ? 0 : heightMap[ix + iz*(gridWidth + 1)];
				Vec3 vec = Vec3(x + ix*tileWidth, y + heightM*height, z + iz*tileLength);
				uint index = IndexGrid(ix,iz,gridWidth, gridLength);
				vertices[index] = vec;
				if(iz < gridLength - 1 && ix != 0 && ix != gridWidth)
				{
					vertices[index + 1] = vec;
				}
			}
		}

		uint indexCount = 6 * gridWidth * gridLength;
		uint* indices = new uint[indexCount];


		#define GRID(argx,argy) ((argx)*2-1)+(argy) * 2 * gridWidth;
		// Loop through every square
		uint i = 0;
		for (uint iz = 0; iz < gridLength; iz++)
		{
			for (uint ix = 0; ix < gridWidth; ix++)
			{
				if (iz < gridLength - 1)
				{
					uint add = (ix != 0) ? 1 : 0;
					if (ix % 2 == iz % 2)
					{
						indices[i++] = IndexGrid(ix, iz,gridWidth,gridLength) + add;
						indices[i++] = IndexGrid(ix, iz + 1, gridWidth, gridLength);
						indices[i++] = IndexGrid(ix + 1, iz + 1, gridWidth, gridLength);
						indices[i++] = IndexGrid(ix + 1, iz, gridWidth, gridLength);
						indices[i++] = IndexGrid(ix, iz, gridWidth, gridLength);
						indices[i++] = IndexGrid(ix + 1, iz + 1, gridWidth, gridLength);
					}
					else
					{
						indices[i++] = IndexGrid(ix, iz, gridWidth, gridLength) + add;
						indices[i++] = IndexGrid(ix, iz + 1, gridWidth, gridLength);
						indices[i++] = IndexGrid(ix + 1, iz, gridWidth, gridLength);
						indices[i++] = IndexGrid(ix + 1, iz, gridWidth, gridLength);
						indices[i++] = IndexGrid(ix, iz + 1, gridWidth, gridLength);
						indices[i++] = IndexGrid(ix + 1, iz + 1, gridWidth, gridLength);
					}
				}
				else
				{
					if (ix % 2 == iz % 2)
					{
						indices[i++] = IndexGrid(ix, iz, gridWidth, gridLength);
						indices[i++] = IndexGrid(ix, iz + 1, gridWidth, gridLength);
						indices[i++] = IndexGrid(ix + 1, iz + 1, gridWidth, gridLength);
						indices[i++] = IndexGrid(ix + 1, iz + 1, gridWidth, gridLength);
						indices[i++] = IndexGrid(ix + 1, iz, gridWidth, gridLength);
						indices[i++] = IndexGrid(ix, iz, gridWidth, gridLength);
					}
					else
					{
						indices[i++] = IndexGrid(ix, iz, gridWidth, gridLength);
						indices[i++] = IndexGrid(ix, iz + 1, gridWidth, gridLength);
						indices[i++] = IndexGrid(ix + 1, iz, gridWidth, gridLength);
						indices[i++] = IndexGrid(ix + 1, iz + 1, gridWidth, gridLength);
						indices[i++] = IndexGrid(ix + 1, iz, gridWidth, gridLength);
						indices[i++] = IndexGrid(ix, iz + 1, gridWidth, gridLength);
					}
				}

			}
		}

		Vec3* normals = CalculateNormals(vertices, vertexCount, indices, indexCount);
		MeshData* data = new MeshData(vertices, vertexCount, indices, indexCount);
		data->AddAttribute(new AttributeData(ATTRIBUTE_NORMAL, normals));

		return data;
	}

}