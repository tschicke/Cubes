#version 330

in vec2 UV;
smooth in vec3 vNormal;

out vec3 color;

uniform sampler2D myTextureSampler;

void main(){
	float diffuseIntensity = clamp(dot(normalize(vNormal), -normalize(vec3(3, -4, -2))), 0.2, 0.8);
	color = texture2D(myTextureSampler, UV).rgb * (vec3(1, 1, 1) * (diffuseIntensity + 0.2));
}