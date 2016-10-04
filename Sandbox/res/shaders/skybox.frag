#version 330 core

in vec3 vert_texCoord;

out vec4 out_color;

uniform samplerCube textureSampler;

void main()
{
	out_color = texture(textureSampler,vert_texCoord);
	//out_color = vec4(vert_texCoord,1.0f);
	//out_color = vec4(1.0f,00.0f,1.0f,1.0f);
	//if(out_color.a < 0.1)
	//	discard;
	//out_color = vec4(finalSpecular.xyz,1.0);
}