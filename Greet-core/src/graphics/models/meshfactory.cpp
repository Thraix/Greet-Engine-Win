#include "meshfactory.h"
#include <logging/logger.h>
namespace greet { namespace model { namespace MeshFactory {
	
	// Calculate a normal of 3 points in space
	math::vec3 calculateNormal(math::vec3 p1, math::vec3 p2, math::vec3 p3)
	{
		math::vec3 v1 = p2 - p1;
		math::vec3 v2 = p3 - p1;
		math::vec3 normal = v1.cross(v2);
		return normal;
	}

	void calculateNormals(math::vec3* vertices, uint vertexCount, uint* indices, uint indexCount, math::vec3* normals)
	{
		math::vec3 faceNormal;
		math::vec3 p1, p2, p3;
		memset(normals, 0, sizeof(float) * 3 * vertexCount);
		for (int i = 0; i < indexCount; i += 3)
		{
			p1 = vertices[indices[i]];
			p2 = vertices[indices[i + 1]];
			p3 = vertices[indices[i + 2]];
			faceNormal = calculateNormal(p1, p2, p3);
			normals[indices[i]] += faceNormal;
			normals[indices[i + 1]] += faceNormal;
			normals[indices[i + 2]] += faceNormal;
		}
		for (int i = 0; i < vertexCount; i++)
		{
			((math::vec3*)normals)[i].normalize();
		}
	}

	// Calculate normals for a mesh
	math::vec3* calculateNormals(math::vec3* vertices, uint vertexCount, uint* indices, uint indexCount)
	{
		math::vec3* normals = new math::vec3[vertexCount];
		calculateNormals(vertices, vertexCount, indices, indexCount, normals);
		return normals;
	}

	MeshData* quad(float x, float y, float z, float width, float length)
	{
		math::vec3 vertices[4];
		float halfWidth = width / 2.0f;
		float halfLength = length / 2.0f;
		vertices[0]  = math::vec3(x-halfWidth, y, z-halfLength);
		vertices[1]  = math::vec3(x+halfWidth, y, z-halfLength);
		vertices[2]  = math::vec3(x+halfWidth, y, z+halfLength);
		vertices[3]  = math::vec3(x-halfWidth, y, z+halfLength);

		math::vec3 normals[4];	
		normals[0]  = math::vec3(0.0f, 1.0f, 0.0f);
		normals[1]  = math::vec3(0.0f, 1.0f, 0.0f);
		normals[2]  = math::vec3(0.0f, 1.0f, 0.0f);
		normals[3]  = math::vec3(0.0f, 1.0f, 0.0f);

		uint* indices = new uint[6]{0,1,2,0,2,3};
		MeshData* meshdata = new MeshData(vertices,4,indices,6);
		meshdata->addAttribute(new AttributeData(ATTRIBUTE_NORMAL,normals));
		return meshdata;
	}
	// x, y, z
	MeshData* cube(float x, float y, float z, float width, float length, float height)	
	{
		math::vec3* vertices = new math::vec3[8];
		float halfWidth = width / 2.0f;
		float halfLength = length / 2.0f;
		float halfHeight = height / 2.0f;
		vertices[0]  = math::vec3(x-halfWidth, y-halfHeight, z-halfLength);
		vertices[1]  = math::vec3(x-halfWidth, y+halfHeight, z-halfLength);
		vertices[2]  = math::vec3(x-halfWidth, y+halfHeight, z+halfLength);
		vertices[3]  = math::vec3(x-halfWidth, y-halfHeight, z+halfLength);

		vertices[4]  = math::vec3(x+halfWidth, y-halfHeight, z-halfLength);
		vertices[5]  = math::vec3(x+halfWidth, y+halfHeight, z-halfLength);
		vertices[6]  = math::vec3(x+halfWidth, y+halfHeight, z+halfLength);
		vertices[7]  = math::vec3(x+halfWidth, y-halfHeight, z+halfLength);

		float* normals = new float[8 * 3];
		((math::vec3*)normals)[0] = math::vec3(-1.0f, -1.0f, -1.0f);
		((math::vec3*)normals)[1] = math::vec3(-1.0f,  1.0f, -1.0f);
		((math::vec3*)normals)[2] = math::vec3(-1.0f,  1.0f,  1.0f);
		((math::vec3*)normals)[3] = math::vec3(-1.0f, -1.0f,  1.0f);
		((math::vec3*)normals)[4] = math::vec3( 1.0f, -1.0f, -1.0f);
		((math::vec3*)normals)[5] = math::vec3( 1.0f,  1.0f, -1.0f);
		((math::vec3*)normals)[6] = math::vec3( 1.0f,  1.0f,  1.0f);
		((math::vec3*)normals)[7] = math::vec3( 1.0f, -1.0f,  1.0f);
	
		uint* indices = new uint[36]{
			 0, 2, 1, 0, 3, 2,
			 3, 6, 2, 3, 7, 6,
			 7, 5, 6, 7, 4, 5,
			 4, 1, 5, 4, 0, 1,
			 2, 5, 1, 2, 6, 5,
			 3, 0, 4, 3, 4, 7 };

		MeshData* meshdata = new MeshData(vertices,8,indices,36);
		meshdata->addAttribute(new AttributeData(ATTRIBUTE_NORMAL,normals));
		return meshdata;
	}

	MeshData* tetrahedron(float x, float y, float z, float size)
	{
		float tan30 = 0.5773502f;  //   tan(30/180*PI)
		float cos30 = 1.1547005f; //   1 / cos(30/180*PI) 
		float halfSize = size * 0.5f;
		float l1 = halfSize*cos30;
		float l2 = halfSize*tan30; // 
		float height = size*0.8164965f;// Height of tetrahedron
		float corner = size*0.4082483f; // size/sqrt(6) -> Center to corner
		float face = height - corner; // Center to face 

		math::vec3 v1 = math::vec3(x, y-face, z + l1);
		math::vec3 v2 = math::vec3(x + halfSize, y - face, z - l2);
		math::vec3 v3 = math::vec3(x - halfSize, y - face, z - l2);
		math::vec3 v4 = math::vec3(x, y + corner, z);


		math::vec3* vertices = new math::vec3[4];
		vertices[0] = v1;
		vertices[1] = v2;
		vertices[2] = v3;
		vertices[3] = v4;

		
		float* normals = new float[4 * 3];

		((math::vec3*)normals)[0] = (v1 - math::vec3(x, y, z)).normalize();
		((math::vec3*)normals)[1] = (v2 - math::vec3(x, y, z)).normalize();
		((math::vec3*)normals)[2] = (v3 - math::vec3(x, y, z)).normalize();
		((math::vec3*)normals)[3] = (v4 - math::vec3(x, y, z)).normalize();

		uint* indices = new uint[12]{ 0, 2, 1, 1, 3, 0, 2, 0, 3, 1, 2, 3};
		MeshData* meshdata = new MeshData(vertices, 4, indices, 12);
		meshdata->addAttribute(new AttributeData(ATTRIBUTE_NORMAL,normals));
		return meshdata;
	}

	MeshData* grid(float x, float y, float z, float width, float length, uint gridWidth, uint gridLength)
	{
		return grid(x,y,z,width,length,gridWidth,gridLength,NULL,0);
	}

	MeshData* grid(float x, float y, float z, float width, float length, uint gridWidth, uint gridLength, float* heightMap, float height)
	{
		if (gridWidth < 1 || gridLength < 1)
			return quad(x, y, z, width, length);

		float tileWidth = width / (float)gridWidth;
		float tileLength = length / (float)gridLength;

		uint vertexCount = (gridWidth + 1) * (gridLength+ 1);

		math::vec3* vertices = new math::vec3[vertexCount];

		// decenter x and y
		x -= width / 2.0f;
		z -= length / 2.0f;


		for (uint iz = 0; iz <= gridLength; iz++)
		{
			for (uint ix = 0; ix <= gridWidth; ix++)
			{
				float heightM = heightMap == NULL ? 0 : heightMap[ix + iz*(gridWidth + 1)];
				vertices[ix + iz*(gridWidth + 1)] = math::vec3(x + ix*tileWidth, y + heightM*height, z + iz*tileLength);
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
					indices[i++] = ix + iz*(gridWidth + 1);
					indices[i++] = ix + (iz + 1)*(gridWidth + 1);
					indices[i++] = ix + 1 + (iz + 1)*(gridWidth + 1);
					indices[i++] = ix + iz*(gridWidth + 1);
					indices[i++] = ix + 1 + (iz + 1)*(gridWidth + 1);
					indices[i++] = ix + 1 + iz*(gridWidth + 1);
				}
				else
				{
					indices[i++] = ix + iz*(gridWidth + 1);
					indices[i++] = ix + (iz + 1)*(gridWidth + 1);
					indices[i++] = ix + 1 + iz*(gridWidth + 1);
					indices[i++] = ix + 1 + iz*(gridWidth + 1);
					indices[i++] = ix + (iz + 1)*(gridWidth + 1);
					indices[i++] = ix + 1 + (iz + 1) * (gridWidth + 1);
				}
			}
		}

		math::vec3* normals = calculateNormals(vertices, vertexCount, indices, indexCount);
		MeshData* data = new MeshData(vertices, vertexCount, indices, indexCount);
		data->addAttribute(new AttributeData(ATTRIBUTE_NORMAL, normals));

		return data;
	}

}}}