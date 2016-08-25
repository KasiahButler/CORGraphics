#define GLEW_STATIC

#include "GLEW\glew.h"

#include "crenderutils.h"
#include "vertex.h"

Geometry makeGeometry(struct Vertex *verts, size_t vsize, unsigned int *tris, size_t tsize)
{
	Geometry retVal;
	retVal.size = tsize;

	
	//Define all the Variables
	glCreateBuffers(1, &retVal.vbo);
	glCreateBuffers(1, &retVal.ibo);
	glCreateVertexArrays(1, &retVal.vao);

	//Scope all the variables
	glBindVertexArray(retVal.vao);
	glBindBuffer(GL_ARRAY_BUFFER, retVal.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retVal.ibo);

	//Initialize the Variables
	glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(Vertex), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tsize * sizeof(unsigned), tris, GL_STATIC_DRAW);

	//Attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)16);
	

	//Unscope the Variables
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return retVal;
}

void freeGeometry(Geometry &geo)
{
	glDeleteBuffers(1, &geo.vbo);
	glDeleteBuffers(1, &geo.ibo);
	glDeleteVertexArrays(1, &geo.vao);
	geo = { 0, 0, 0, 0 };
}