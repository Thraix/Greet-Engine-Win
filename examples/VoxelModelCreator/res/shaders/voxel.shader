//vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 3) in vec3 normal;

out vec4 vert_color;

uniform vec4 mat_color;
uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{

	vec4 worldPosition = transformationMatrix * vec4(position, 1.0f);
	vec4 positionRelativeToCamera = viewMatrix * worldPosition;
	gl_Position = projectionMatrix * positionRelativeToCamera;

	vert_color = mat_color;

	// X major
	if (abs(normal.x) > abs(normal.y) && abs(normal.x) > abs(normal.z))
		vert_color *= vec4(1.0f, 1.0f, 1.0f, 1.0f);
	// Y major
	else if (abs(normal.y) > abs(normal.z))
		vert_color *= vec4(0.9f, 0.9f, 0.9f, 1.0f);
	// Z major
	else
		vert_color *= vec4(0.8f, 0.8f, 0.8f, 1.0f);
}

//fragment
#version 330 core

in vec4 vert_color;
out vec4 out_color;

void main()
{
	out_color = vert_color;
}