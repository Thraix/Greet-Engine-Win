#version 330 core

flat in vec4 vert_color;
flat in float visibility;


out vec4 out_color;
uniform vec4 fogColor = vec4(0.125,0.125,0.125,1);

void main()
{
	out_color = vert_color;
	out_color = mix(vec4(fogColor.rgb,out_color.a),vec4(out_color.rgb,out_color.a),visibility);
}
