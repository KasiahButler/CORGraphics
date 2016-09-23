#pragma once

struct Geometry
{
	unsigned vbo, ibo, vao, size;

	//Vertex Buffer Object : Array of Vertices
	//Index Buffer Object : Array of Indicies (Triangles)
	//Vertex Array Object : Groups the two with formatting;
	//Size : Number of Triangles
};

struct Shader
{
	unsigned handle;

	bool depthTest;
	bool additiveBlend;
	bool faceCulling;
};

struct Texture
{
	unsigned handle;
	unsigned width, height, format;
};

struct Framebuffer
{
	unsigned handle;
	unsigned width, height, nColors;

	Texture depth;
	Texture colors[8];
};