#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 color;
layout(location = 3) in vec3 normal;

out vec4 vert_color;
out vec2 vert_texCoord;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;
out float visibility;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 light_position = vec3(0.0,0.0,-10.0);

const float density = 0.007;
const float gradient = 1.5;

void main()
{

	vec4 worldPosition = transformationMatrix * vec4(position,1.0f);
	vec4 positionRelativeToCamera = viewMatrix * worldPosition;
	gl_Position = projectionMatrix * positionRelativeToCamera;
	vert_color = vec4(color.b, color.g, color.r, color.a);

	vert_texCoord = texCoord;
	surfaceNormal = (transformationMatrix * vec4(normal,0.0)).xyz;
	toLightVector = light_position - worldPosition.xyz;
	toCameraVector = (inverse(viewMatrix) * vec4(0,0,0,1)).xyz - worldPosition.xyz;

	float distance = length(positionRelativeToCamera.xyz);
	visibility = exp(-pow((distance*density),gradient));
	visibility = clamp(visibility,0.0,1.0);
}