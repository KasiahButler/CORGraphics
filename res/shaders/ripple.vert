#version 430

layout(location = 0) in vec4 position;
layout(location = 2) in vec4 normal;
layout(location = 3) in vec2 texcoord;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 proj;

layout(location = 6) uniform vec4 SSFT;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vUV;

void main()
{
	float rSpeed = SSFT.x;
	float rScale = SSFT.y;
	float rFrequency = SSFT.z;
	float dt = SSFT.w;

	vec4 rPosition = (view * model * position);
	float offset = (rPosition.x * rPosition.x) + (rPosition.z * rPosition.z);
	rPosition.y += rScale * sin(dt * rSpeed + offset * rFrequency);

	vPosition = rPosition.xyz;
	vNormal = (view * model * normal).xyz;
	vUV = texcoord;

	gl_Position = proj * view * model * rPosition;
}