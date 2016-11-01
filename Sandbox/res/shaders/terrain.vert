#version 330 core

layout(location = 0) in vec3 position;
in vec4 color;
in vec3 normal;
out vec4 vert_color;
out vec2 vert_texCoord;
out vec3 toCameraVector;
out float visibility;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform float amplitude;

const float density = 0.0007;
const float gradient = 1.5;

out Vertex
{
	vec3 realPos;
	vec4 realColor;
} vertex;

void main()
{
	vertex.realPos = position;
	if(position.y < 0.45*amplitude)
	{
		vertex.realColor = vec4(0,0,pow(position.y/amplitude/0.45,4.0f),1);
		vertex.realPos.y = 0.45*amplitude;
	}
	else if(position.y < 0.48*amplitude)
	{
		vertex.realColor = vec4(0.95,0.9,0.8,1.0);
	}
	else if(position.y < 0.58*amplitude)
	{
		vertex.realColor = vec4(101/255.0,186/255.0,89/255.0,1);
	}
	else if(position.y < 0.65*amplitude)
	{
		vertex.realColor = vec4(0.45,0.45,0.6,1.0);
		vertex.realPos.y = (pow(vertex.realPos.y / amplitude - 0.58, 0.6) + 0.58) * amplitude;
	}
	else
	{
		vertex.realColor = vec4(0.9,0.9,1,1);
		vertex.realPos.y = (pow(vertex.realPos.y / amplitude - 0.58, 0.6) + 0.58) * amplitude;
	}
	vertex.realPos.y*=2;

	vec4 worldPosition = transformationMatrix * vec4(vertex.realPos,1.0f);
	vec4 positionRelativeToCamera = viewMatrix * worldPosition;

	gl_Position = projectionMatrix * positionRelativeToCamera;

	toCameraVector = (inverse(viewMatrix) * vec4(0,0,0,1)).xyz - worldPosition.xyz;

	float distance = length(positionRelativeToCamera.xyz);
	visibility = exp(-pow((distance*density),gradient));
	visibility = clamp(visibility,0.0,1.0);
}
