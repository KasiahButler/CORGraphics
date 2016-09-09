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

void Ndraw(const Shader &s, const Geometry &g, const float M[16], const float V[16], const float P[16]);

Geometry loadOBJ(const char *path);

struct Texture
{
	unsigned handle;
	unsigned width, height, format;
};

Texture makeTexture(unsigned width, unsigned height, unsigned format, const unsigned char *pixels);
Texture makeTextureF(unsigned square, const float *pixels);
void freeTexture(Texture &t);

void drawPhong(const Shader &s, const Geometry &g, const float M[16], const float V[16], const float P[16]);
