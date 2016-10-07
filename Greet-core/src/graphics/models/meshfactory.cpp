#include "meshfactory.h"
#include <logging/logger.h>
namespace greet { namespace model { namespace MeshFactory {
	
	math::vec3 calculateNormal(math::vec3 p1, math::vec3 p2, math::vec3 p3)
	{
		// Calculate a normal of 3 points in space
		math::vec3 v1 = p2 - p1;
		math::vec3 v2 = p3 - p1;
		math::vec3 normal = v1.cross(v2);
		return normal;
	}

	float* calculateNormals(float* vertices, uint vertexCount, uint* indices, uint indexCount)
	{
		float* normals = new float[vertexCount*3];
		memset(normals, 0, vertexCount * 3 * sizeof(float));
		math::vec3 faceNormal;
		math::vec3 p1,p2,p3;
		for (int i = 0;i < indexCount;i += 3)
		{
			p1 = ((math::vec3*)vertices)[indices[i]];
			p2 = ((math::vec3*)vertices)[indices[i+1]];
			p3 = ((math::vec3*)vertices)[indices[i+2]];
			faceNormal = calculateNormal(p1,p2,p3);
			//LOG_INFO(p1.x,p1.y,p2.z,p2.x,p2.y,p2.z,p3.x,p3.y,p3.z);
			((math::vec3*)normals)[indices[i]] += faceNormal;
			((math::vec3*)normals)[indices[i+1]] += faceNormal;
			((math::vec3*)normals)[indices[i+2]] += faceNormal;
		}
		for (int i = 0;i < vertexCount;i++)
		{
			((math::vec3*)normals)[i].normalize();
		}
		return normals;
	}

	Mesh* quad(float x, float y, float z, float width, float length)
	{
		float vertices[4 * 3];
		float halfWidth = width / 2.0f;
		float halfLength = length / 2.0f;
		((math::vec3*)vertices)[0]  = math::vec3(x-halfWidth, y, z-halfLength);
		((math::vec3*)vertices)[1]  = math::vec3(x+halfWidth, y, z-halfLength);
		((math::vec3*)vertices)[2]  = math::vec3(x+halfWidth, y, z+halfLength);
		((math::vec3*)vertices)[3]  = math::vec3(x-halfWidth, y, z+halfLength);
		float normals[4 * 3];	
		((math::vec3*)normals)[0]  = math::vec3(0.0f, 1.0f, 0.0f);
		((math::vec3*)normals)[1]  = math::vec3(0.0f, 1.0f, 0.0f);
		((math::vec3*)normals)[2]  = math::vec3(0.0f, 1.0f, 0.0f);
		((math::vec3*)normals)[3]  = math::vec3(0.0f, 1.0f, 0.0f);
		uint indices[6] = {0,1,2,0,2,3};
		Mesh* mesh = new Mesh(vertices,4,indices,6);
		mesh->addAttribute(MESH_NORMALS_LOCATION, 3, normals);
		return mesh;
	}
	// x, y, z
	Mesh* cube(float x, float y, float z, float width, float length, float height)	
	{
		float vertices[8 * 3];
		float halfWidth = width / 2.0f;
		float halfLength = length / 2.0f;
		float halfHeight = height / 2.0f;
		((math::vec3*)vertices)[0]  = math::vec3(x-halfWidth, y-halfHeight, z-halfLength);
		((math::vec3*)vertices)[1]  = math::vec3(x-halfWidth, y+halfHeight, z-halfLength);
		((math::vec3*)vertices)[2]  = math::vec3(x-halfWidth, y+halfHeight, z+halfLength);
		((math::vec3*)vertices)[3]  = math::vec3(x-halfWidth, y-halfHeight, z+halfLength);

		((math::vec3*)vertices)[4]  = math::vec3(x+halfWidth, y-halfHeight, z-halfLength);
		((math::vec3*)vertices)[5]  = math::vec3(x+halfWidth, y+halfHeight, z-halfLength);
		((math::vec3*)vertices)[6]  = math::vec3(x+halfWidth, y+halfHeight, z+halfLength);
		((math::vec3*)vertices)[7]  = math::vec3(x+halfWidth, y-halfHeight, z+halfLength);

		float normals[8 * 3];
		((math::vec3*)normals)[0] = math::vec3(-1.0f, -1.0f, -1.0f);
		((math::vec3*)normals)[1] = math::vec3(-1.0f,  1.0f, -1.0f);
		((math::vec3*)normals)[2] = math::vec3(-1.0f,  1.0f,  1.0f);
		((math::vec3*)normals)[3] = math::vec3(-1.0f, -1.0f,  1.0f);
		((math::vec3*)normals)[4] = math::vec3( 1.0f, -1.0f, -1.0f);
		((math::vec3*)normals)[5] = math::vec3( 1.0f,  1.0f, -1.0f);
		((math::vec3*)normals)[6] = math::vec3( 1.0f,  1.0f,  1.0f);
		((math::vec3*)normals)[7] = math::vec3( 1.0f, -1.0f,  1.0f);
	
		uint indices[36] = {
			 0, 2, 1, 0, 3, 2,
			 3, 6, 2, 3, 7, 6,
			 7, 5, 6, 7, 4, 5,
			 4, 1, 5, 4, 0, 1,
			 2, 5, 1, 2, 6, 5,
			 3, 0, 4, 3, 4, 7 };

		Mesh* mesh = new Mesh(vertices,8,indices,36);
		mesh->addAttribute(MESH_NORMALS_LOCATION, 3, normals);
		return mesh;
	}

	Mesh* tetrahedron(float x, float y, float z, float size)
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

		//LOG_INFO((v1-v2).length(),(v1-v3).length(),(v1-v4).length(),(v2-v3).length(),(v2-v4).length(),(v3-v4).length());

		float vertices[4 * 3];
		((math::vec3*)vertices)[0] = v1;
		((math::vec3*)vertices)[1] = v2;
		((math::vec3*)vertices)[2] = v3;
		((math::vec3*)vertices)[3] = v4;

		
		float normals[4 * 3];

		((math::vec3*)normals)[0] = (v1 - math::vec3(x, y, z)).normalize();//math::vec3(0.0f, -cos30, 0.8164965f).normalize();
		((math::vec3*)normals)[1] = (v2 - math::vec3(x, y, z)).normalize();//math::vec3(0.8164965f*(cos30 - tan30), -0.5f*cos30, -0.5*0.8164965f).normalize();
		((math::vec3*)normals)[2] = (v3 - math::vec3(x, y, z)).normalize();//math::vec3(0.8164965f*(tan30 - cos30), -0.5f*cos30, -0.5*0.8164965f).normalize();
		((math::vec3*)normals)[3] = (v4 - math::vec3(x, y, z)).normalize();//math::vec3(0.0f, 1.0f, 0.0f);

		uint indices[12] = { 0, 2, 1, 1, 3, 0, 2, 0, 3, 1, 2, 3};
		Mesh* mesh = new Mesh(vertices, 12, indices, 12);
		mesh->addAttribute(MESH_NORMALS_LOCATION, 3, normals);
		return mesh;
	}

	Mesh* grid(float x, float y, float z, float width, float length, uint gridWidth, uint gridLength, float* heightMap, float height)
	{
		if (gridWidth < 0 || gridLength < 0)
			return quad(x, y, z, width, length);
		float tileWidth = gridWidth / width;
		float tileLength = gridLength / length;
		uint vertexCount = (gridWidth + 1) * (gridLength + 1);
		float* vertices = new float[vertexCount * 3];
		uint* colors = new uint[vertexCount];
		x -= width / 2.0f;
		z -= length / 2.0f;
		for (uint iz = 0;iz <= gridLength;iz++)
		{
			for (uint ix = 0;ix <= gridWidth;ix++)
			{
				float heightM = heightMap[ix + iz*(gridWidth + 1)];
				((math::vec3*)vertices)[ix + iz*(gridWidth + 1)] = math::vec3(x + ix*tileWidth, y+heightM*height, z + iz*tileLength);
				/*if (heightM < 0.2)
				{
					colors[ix + iz*(gridWidth + 1)] = 0xff0000ff;
				}
				else if (heightM < 0.3)
				{
					colors[ix + iz*(gridWidth + 1)] = 0xffffff00;
				}
				else if (heightM < 0.6)
				{
					colors[ix + iz*(gridWidth + 1)] = 0xff00ff00;
				}
				else if (heightM < 0.8)
				{
					colors[ix + iz*(gridWidth + 1)] = 0xff555555;
				}
				else
				{
					colors[ix + iz*(gridWidth + 1)] = 0xffffffff;		
				}*/
			}
		}
		uint indexCount = 6 * gridWidth * gridLength;
		uint* indices = new uint[indexCount];
		uint i = 0;
		for (uint iz = 0;iz < gridLength;iz++)
		{
			for (uint ix = 0;ix < gridWidth;ix++)
			{
				indices[i++] = ix + iz*(gridWidth + 1);
				indices[i++] = ix + (iz+1)*(gridWidth + 1);
				indices[i++] = ix+1 + (iz+1)*(gridWidth + 1);
				indices[i++] = ix + iz*(gridWidth + 1);
				indices[i++] = ix+1 + (iz+1)*(gridWidth + 1);
				indices[i++] = ix+1 + iz*(gridWidth + 1);
			}
		}
		float* normals = calculateNormals(vertices,vertexCount,indices,indexCount);
		Mesh* mesh = new Mesh(vertices,vertexCount,indices,indexCount);
		mesh->addAttribute(MESH_NORMALS_LOCATION, 3, normals);
		//mesh->addAttribute(MESH_COLORS_LOCATION, 4, colors);
		return mesh;
	}

}}}