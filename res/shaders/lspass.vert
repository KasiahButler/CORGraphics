#version 430

layout(location = 0) in vec4 position;
layout(location = 3) in vec2 texcoord;

layout(location = 0) uniform mat4 camView;
layout(location = 7) uniform mat4 light;

vec3 viewPos = vec3(camView[0][0], camView[1][1], camView[2][2]);
vec3 lightPos = vec3(light[0][0], light[1][1], light[2][2]);

out vec2 vUV;
out vec3 halfwayDir;
out mat4 view;
out mat4 lightView;

void main()
{
	vec3 lightDir = normalize(lightPos - position.xyz);
	vec3 viewDir = normalize(viewPos - position.xyz);
	vec3 halfwayDir = normalize(lightDir + viewDir);

	view = camView;
	lightView = light;

	vUV = texcoord;
	gl_Position = position;
}