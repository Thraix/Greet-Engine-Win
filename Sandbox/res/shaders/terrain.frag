#version 330 core

in vec4 vert_color;

in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;
in float visibility;

out vec4 out_color;

uniform vec3 light_color = vec3(1.0f,1.0f,1.0f);
uniform vec3 fogColor = vec3(0,0,1);
uniform float shadeDamper = 10.0;
uniform float reflectivity = 1;

void main()
{
	out_color = vert_color;
	out_color *= vec4(0.5f,0.5f,0.5f,1.0f);
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);
	//out_color = vec4(unitNormal,1.0);

	float nDot = dot(unitNormal, unitLightVector);
	float brightness = max(nDot,0.3*);
	vec3 diffuse = light_color * brightness;
	out_color *= vec4(diffuse,1.0f);

	//float luminance = (out_color.r + out_color.g + out_color.b)/3.0;
	//out_color.rgb = floor(luminance * 4.0)/4.0 * fogColor;

	//out_color = mix(vec4(fogColor.xyz,1.0),vec4(out_color.rgb,1.0),visibility);
	//out_color = vec4(visibility,1.0,1.0,1.0);
	//out_color = vec4(finalSpecular.xyz,1.0);
	//out_color = vec4(out_color.rgb*visibility,1.0);
	//out_color.a = 1.0f;
	//out_color = vec4(surfaceNormal*0.5f+0.5f,1.0f);
	//out_color = vec4(unitLightVector,1);

}
