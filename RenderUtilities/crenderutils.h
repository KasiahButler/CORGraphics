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