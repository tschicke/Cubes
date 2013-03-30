#version 330

in vec2 UV;
smooth in vec3 vNormal;

out vec3 color;

uniform sampler2D myTextureSampler;
uniform vec3 testColor;//test only

void main(){
	vec2 glUV;
	glUV.x = UV.x;
	glUV.y = 1.0 - UV.y;
	float diffuseIntensity = clamp(dot(normalize(vNormal), -normalize(vec3(3, -4, -2))), 0.2, 0.8);
	color = texture2D(myTextureSampler, glUV).rgb * (testColor * (diffuseIntensity + 0.2));
}