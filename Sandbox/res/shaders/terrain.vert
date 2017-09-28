#version 330 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec4 color;
layout(location = 3) in vec3 normal;

flat out vec4 vert_color;
flat out float visibility;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 light_color = vec3(1.0f,0.96f,0.9f);
const float density = 0.003;
const float gradient = 1.5;

void main()
{
	vert_color = vec4(color.b, color.g, color.r, color.a);
	vec4 worldPosition = transformationMatrix * vec4(position,1.0f);
	vec4 positionRelativeToCamera = viewMatrix * worldPosition;
	gl_Position = projectionMatrix * positionRelativeToCamera;

	vec3 surfaceNormal = (transformationMatrix * vec4(normal,0.0)).xyz;
	vec3 toLightVector = vec3(-10, 10, 0);
	vec3 toCameraVector = (inverse(viewMatrix) * vec4(0,0,0,1)).xyz - worldPosition.xyz;

	float distance = length(positionRelativeToCamera.xyz);
	visibility = exp(-pow((distance*density),gradient));
	visibility = clamp(visibility,0.0,1.0);
	vert_color *= vec4(0.8f,0.8f,0.8f,1.0f);
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);

	float nDot = dot(unitNormal, unitLightVector);
	float brightness = max(nDot,0.4);
	vec3 diffuse = light_color * brightness;
	vert_color *= vec4(diffuse,1.0f);
}
