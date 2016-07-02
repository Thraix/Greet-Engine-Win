#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 color;
layout(location = 3) in vec3 normal;

out vec4 vert_color;
out vec2 vert_texCoord;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{
	vec4 worldPosition = transformationMatrix * vec4(position,1.0f);
	gl_Position = projectionMatrix * viewMatrix * worldPosition;
	vert_color = vec4(color.b, color.g, color.r, color.a);
	vert_texCoord = texCoord;
}