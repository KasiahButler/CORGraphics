#define GLEW_STATIC

#include "GLEW\glew.h"

#include "crenderutils.h"
#include "vertex.h"

#include <fstream>
#include <cstdio>

#include <string>
#include <iostream>

Geometry makeGeometry(const Vertex *verts, size_t vsize, const unsigned int *tris, size_t tsize)
{
	Geometry retVal;
	retVal.size = tsize;

	
	//Define all the Variables
	glGenBuffers(1, &retVal.vbo);
	glGenBuffers(1, &retVal.ibo);
	glGenVertexArrays(1, &retVal.vao);

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

Shader makeShader(const char * vsource, const char * fsource)
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

char *loadTextFile(const char *fileLocation)
{
	std::ifstream myFile(fileLocation, std::ios::in);
	if (myFile.is_open())
	{
		const int fileSize = 1024;
		char *textString = new char[fileSize];
		int currentChar = 0;

		while (!myFile.eof() && currentChar < fileSize)
		{
			myFile.get(textString[currentChar]);
			++currentChar;
		}

		textString[currentChar - 1] = '\0';

		return textString;
	} 

	return nullptr;
}

Shader loadShader(const char * vpath, const char * fpath)
{
	char *vsource = loadTextFile(vpath);
	char *fsource = loadTextFile(fpath);

	Shader returnShader = makeShader(vsource, fsource);

	delete[] vsource;
	delete[] fsource;

	return returnShader;
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

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "OBJ\tiny_obj_loader.h"
#include <random>

Geometry loadOBJ(const char *path)
{
	//TinyOBJ required code for setup
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	//Setsup and confirms that an object can be loaded
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

	//Builds an array of Verticies and Triangles to work with based on .obj size
	Vertex   *verts = new Vertex[attrib.vertices.size() / 3];
	unsigned * tris = new unsigned[shapes[0].mesh.indices.size()];

	//Breaks up the .obj info so that it is in a format we can use
	for (int i = 0; i < attrib.vertices.size() / 3; ++i)
	{
		verts[i] = { attrib.vertices[i * 3],
			attrib.vertices[i * 3 + 1],
			attrib.vertices[i * 3 + 2], 1 };
	}

	for (int i = 0; i < shapes[0].mesh.indices.size(); ++i)
		tris[i] = shapes[0].mesh.indices[i].vertex_index;

	//Applies the .obj data to our Geometry class so it can be drawn
	Geometry retval = makeGeometry(verts, attrib.vertices.size() / 3,
		tris, shapes[0].mesh.indices.size());

	//Clear out data from the .obj
	delete[] verts;
	delete[] tris;

	return retval;
}