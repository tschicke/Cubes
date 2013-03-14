#version 330

in vec2 UV;
smooth in vec3 vNormal;

out vec3 color;

uniform sampler2D myTextureSampler;

void main(){
	vec2 glUV;
	glUV.x = UV.x;
	glUV.y = 1.0 - UV.y;
	float diffuseIntensity = clamp(dot(normalize(vNormal), -normalize(vec3(3, -4, -2))), 0.2, 0.8);
	color = texture2D(myTextureSampler, glUV).rgb * (vec3(1, 1, 1) * (diffuseIntensity + 0.2));
}