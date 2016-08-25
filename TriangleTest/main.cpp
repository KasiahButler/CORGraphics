#include "crenderutils.h"
#include "window.h"
#include "vertex.h"

// This is a branch Test

int main()
{
	Window window;
	window.init();

	Vertex verts[3] = { {0, 0.5f, 0, 1}, {0.5f, -0.5f, 0, 1}, {-0.5f, -0.5f, 0, 1} };
	unsigned tris[3] = {0, 1, 2};

	const char vsource[] =
		"#version 150\n"
		"in vec4 position;"
		"void main() { gl_Position = position; }";

	const char fsource[] =
		"#version 150\n"
		"out vec4 outColor;"
		"void main () { outColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); }; ";

	Geometry geometry = makeGeometry(verts, 3, tris, 3);
	Shader shader = makesShader(vsource, fsource);

	while (window.step())
	{
		draw(shader, geometry);
	}

	window.term();

	return 0;
}