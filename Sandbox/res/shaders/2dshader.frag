#version 330

in vec4 vert_color;

out vec4 out_color;

void main()
{
	out_color = vec4(vert_color.rgb,1.0f);
}