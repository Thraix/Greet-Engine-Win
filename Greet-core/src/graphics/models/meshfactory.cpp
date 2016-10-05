#include "meshfactory.h"
#include <logging/logger.h>
namespace greet { namespace model { namespace MeshFactory {
	
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
		float vertices[6 * 4 * 3];
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

		((math::vec3*)vertices)[8]  = math::vec3(x-halfWidth, y-halfHeight, z-halfLength);
		((math::vec3*)vertices)[9]  = math::vec3(x+halfWidth, y-halfHeight, z-halfLength);
		((math::vec3*)vertices)[10]  = math::vec3(x+halfWidth, y-halfHeight, z+halfLength);
		((math::vec3*)vertices)[11]  = math::vec3(x-halfWidth, y-halfHeight, z+halfLength);

		((math::vec3*)vertices)[12]  = math::vec3(x-halfWidth, y+halfHeight, z-halfLength);
		((math::vec3*)vertices)[13]  = math::vec3(x+halfWidth, y+halfHeight, z-halfLength);
		((math::vec3*)vertices)[14]  = math::vec3(x+halfWidth, y+halfHeight, z+halfLength);
		((math::vec3*)vertices)[15]  = math::vec3(x-halfWidth, y+halfHeight, z+halfLength);
		
		((math::vec3*)vertices)[16]  = math::vec3(x-halfWidth, y-halfHeight, z-halfLength);
		((math::vec3*)vertices)[17]  = math::vec3(x+halfWidth, y-halfHeight, z-halfLength);
		((math::vec3*)vertices)[18]  = math::vec3(x+halfWidth, y+halfHeight, z-halfLength);
		((math::vec3*)vertices)[19]  = math::vec3(x-halfWidth, y+halfHeight, z-halfLength);

		((math::vec3*)vertices)[20]  = math::vec3(x-halfWidth, y+halfHeight, z+halfLength);
		((math::vec3*)vertices)[21]  = math::vec3(x+halfWidth, y+halfHeight, z+halfLength);
		((math::vec3*)vertices)[22]  = math::vec3(x+halfWidth, y-halfHeight, z+halfLength);
		((math::vec3*)vertices)[23]  = math::vec3(x-halfWidth, y-halfHeight, z+halfLength);
		float normals[6 * 4 * 3];
		for (int i = 0;i < 4;i++)
		{
			((math::vec3*)normals)[0 + i] = math::vec3(-1.0f, 0.0f, 0.0f);
			((math::vec3*)normals)[4 + i] = math::vec3( 1.0f, 0.0f, 0.0f);
			((math::vec3*)normals)[8 + i] = math::vec3(0.0f, -1.0f, 0.0f);
			((math::vec3*)normals)[12 + i] = math::vec3(0.0f, 1.0f, 0.0f);
			((math::vec3*)normals)[16 + i] = math::vec3(0.0f, 0.0f, -1.0f);
			((math::vec3*)normals)[20 + i] = math::vec3(0.0f, 0.0f, 1.0f);
		}

		uint indices[36] = {
			 0, 1, 2, 0, 2, 3,
			 4, 5, 6, 4, 6, 7,
			 8, 9,10, 8,10,11,
			12,13,14,12,14,15,
			16,17,18,16,18,19,
			20,21,22,20,22,23 };

		Mesh* mesh = new Mesh(vertices,4*6,indices,36);
		mesh->addAttribute(MESH_NORMALS_LOCATION, 3, normals);
		return mesh;
	}

	Mesh* tetrahedron(float x, float y, float z, float size)
	{
		float vertices[4 * 3 * 3];
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

		LOG_INFO((v1-v2).length(),(v1-v3).length(),(v1-v4).length(),(v2-v3).length(),(v2-v4).length(),(v3-v4).length());

		((math::vec3*)vertices)[0] = v2;
		((math::vec3*)vertices)[1] = v1;
		((math::vec3*)vertices)[2] = v3;

		((math::vec3*)vertices)[3] = v1;
		((math::vec3*)vertices)[4] = v2;
		((math::vec3*)vertices)[5] = v4;

		((math::vec3*)vertices)[6] = v2;
		((math::vec3*)vertices)[7] = v3;
		((math::vec3*)vertices)[8] = v4;

		((math::vec3*)vertices)[9] = v3;
		((math::vec3*)vertices)[10] = v1;
		((math::vec3*)vertices)[11] = v4;
		float normals[4 * 4 * 3];
		for (int i = 0;i < 3;i++)
		{
			((math::vec3*)normals)[0 + i] = math::vec3(0.0f, -1.0f, 0.0f);
			((math::vec3*)normals)[3 + i] = math::vec3(0.8164965f*(cos30-tan30), 0.5f*cos30, 0.5*0.8164965f).normalize();
			((math::vec3*)normals)[6 + i] = math::vec3(0.0f,cos30, -0.8164965f).normalize();
			((math::vec3*)normals)[9 + i] = math::vec3(0.8164965f*(tan30-cos30), 0.5f*cos30, 0.5*0.8164965f).normalize();
		}
		uint indices[12] = { 0, 1, 2, 3,4,5,6,7,8,9,10,11 };
		Mesh* mesh = new Mesh(vertices, 12, indices, 12);
		mesh->addAttribute(MESH_NORMALS_LOCATION, 3, normals);
		return mesh;
	}

}}}