#version 330 core

in vec4 vert_color;
in vec2 vert_texCoord;

out vec4 out_color;

uniform sampler2D textureSampler;

void main()
{
	out_color = texture(textureSampler,vert_texCoord);
	if(out_color.a < 0.1)
		discard;
	//out_color = vec4(finalSpecular.xyz,1.0);
}