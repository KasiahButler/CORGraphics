#version 330

layout(location = 0) in vec4 position;
layout(location = 2) in vec4 normal;
layout(location = 3) in vec2 texCoord;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 proj;

out vec3 gNormal;
out vec3 gPosition;
out vec2 gUV;

main()
{
	gNormal = (model * view * normal).xyz;
	gPosition = (model * view * position).xyz;
	gUV = texCoord;

	gl_Position = model * view * proj * position;
}