//vertex
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texId;
layout(location = 3) in vec4 color;

uniform mat3 projectionMatrix = mat3(1);

out DATA
{
	vec2 position;
	vec2 texCoord;
	float texId;
	vec4 color;
} vs_out;

void main()
{
	vs_out.position = (projectionMatrix * vec3(position, 1.0)).xy;
	vs_out.texCoord = vec2(texCoord.x, 1 - texCoord.y);
	vs_out.texId = texId;
	vs_out.color = vec4(color.z, color.y, color.x, color.w);
	gl_Position = vec4(vs_out.position,1.0,1.0);
}

//fragment
#version 330 core

uniform sampler2D textures[32];

out vec4 color;

in DATA
{
	vec2 position;
	vec2 texCoord;
	float texId;
	vec4 color;
} fs_in;

void main()
{
	color = fs_in.color;
	if (fs_in.texId > 0)
	{
		int tid = int(fs_in.texId - 0.5);
		//color = vec4(fs_in.texId-0.5, 0, 0, 1);
		color *= texture(textures[tid], fs_in.texCoord);
	}
	//color = vec4(1, 1, 1, 1);
}