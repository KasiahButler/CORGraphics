#pragma once
#include "vertex.h"

struct Geometry
{
	unsigned vbo, ibo, vao, size;

	//Vertex Buffer Object : Array of Vertices
	//Index Buffer Object : Array of Indicies (Triangles)
	//Vertex Array Object : Groups the two with formatting;
	//Size : Number of Triangles
};

Geometry makeGeometry(const Vertex *verts, size_t vsize, const unsigned int *tris, size_t tsize);

void freeGeometry(Geometry &);

struct Shader
{
	unsigned handle;
};

Shader makeShader(const char *vsource, const char *fsource);

Shader loadShader(const char *vpath, const char *fpath);

void freeShader(Shader &);

void draw(const Shader &, const Geometry &);

Geometry loadOBJ(const char *path);