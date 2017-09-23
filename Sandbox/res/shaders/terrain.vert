#version 330 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec4 color;
layout(location = 3) in vec3 normal;

flat out vec4 vert_color;
flat out vec3 toCameraVector;
flat out vec3 surfaceNormal;
flat out vec3 toLightVector;
flat out float visibility;

uniform float time;
uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 light_position = vec3(0.0,1000.0,0.0);
const float density = 0.007;
const float gradient = 1.5;

void main()
{
	vert_color = vec4(color.b, color.g, color.r, color.a);
	vec4 worldPosition = transformationMatrix * vec4(position,1.0f);
	vec4 positionRelativeToCamera = viewMatrix * worldPosition;
	gl_Position = projectionMatrix * positionRelativeToCamera;

	surfaceNormal = (transformationMatrix * vec4(normal,0.0)).xyz;
	toLightVector = vec3(-10, 10, 0);
	toCameraVector = (inverse(viewMatrix) * vec4(0,0,0,1)).xyz - worldPosition.xyz;

	float distance = length(positionRelativeToCamera.xyz);
	visibility = exp(-pow((distance*density),gradient));
	visibility = clamp(visibility,0.0,1.0);
	//vert_color = vec4(position,1);
}
