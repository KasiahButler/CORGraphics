#pragma once

struct Geometry
{
	unsigned vbo, ibo, vao, size;

	//Vertex Buffer Object : Array of Vertices
	//Index Buffer Object : Array of Indicies (Triangles)
	//Vertex Array Object : Groups the two with formatting;
	//Size : Number of Triangles
};

Geometry makeGeometry(struct Vertex *verts, size_t vsize, unsigned int *tris, size_t tsize);

void freeGeometry(Geometry &);

struct Shader
{
	unsigned handle;
};

Shader makesShader(const char *vsource, const char *fsource);

void freeShader(Shader &);

void draw(const Shader &, const Geometry &);