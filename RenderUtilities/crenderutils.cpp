#define GLEW_STATIC

#include "GLEW\glew.h"

#include "crenderutils.h"
#include "vertex.h"

#include <cstdio>

Geometry makeGeometry(const Vertex *verts, size_t vsize, const unsigned int *tris, size_t tsize)
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

Shader makesShader(const char * vsource, const char * fsource)
{
	Shader retVal;

	//Create all the variables
	retVal.handle = glCreateProgram();

	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);

	//Initialize all of the Variables
	glShaderSource(vs, 1, &vsource, NULL);
	glShaderSource(fs, 1, &fsource, NULL);

	//Compile the Shaders
	glCompileShader(vs);
	glCompileShader(fs);

	//Link all Shaders into a single Program
	glAttachShader(retVal.handle, vs);
	glAttachShader(retVal.handle, fs);
	glLinkProgram(retVal.handle);

	//Delete out the Shaders once they are linked
	glDeleteShader(vs);
	glDeleteShader(fs);

	return retVal;
}

void freeShader(Shader &shader)
{
	glDeleteProgram(shader.handle);
	shader.handle = NULL;
}

void draw(const Shader &shader, const Geometry &geometry)
{
	//Uses the Shader Program created at handle
	glUseProgram(shader.handle);
	
	//Binding VAO also binds IBO (Tri) and VBO (Verts)
	glBindVertexArray(geometry.vao);
	
	//Draw the vertices that are currently bound using array of indices
	//If IBO is bound, don't need to proved Indicies (NULL in this case)
	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, NULL);
}
