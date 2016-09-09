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
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::POSITION);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::COLOR);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::NORMAL);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::TEXCOORD);
	

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

void Ndraw(const Shader &s, const Geometry &g, const float M[16], const float V[16], const float P[16])
{
	glEnable(GL_CULL_FACE);
	//glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glUseProgram(s.handle);
	glBindVertexArray(g.vao);

	glUniformMatrix4fv(0, 1, GL_FALSE, P);
	glUniformMatrix4fv(1, 1, GL_FALSE, V);
	glUniformMatrix4fv(2, 1, GL_FALSE, M);

	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
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

	int vsize = shapes[0].mesh.indices.size();

	//Builds an array of Verticies and Triangles to work with based on .obj size
	Vertex   *verts = new Vertex[vsize];
	unsigned *tris = new unsigned[vsize];

	//Breaks up the .obj info so that it is in a format we can use
	for (int i = 0; i < vsize; ++i)
	{
		auto ind = shapes[0].mesh.indices[i];

		const float *n =   &attrib.normals[ind.normal_index * 3];
		const float *p =  &attrib.vertices[ind.vertex_index * 3];

		verts[i].position = glm::vec4(p[0], p[1], p[2], 1.f);
		verts[i].normal =   glm::vec4(n[0], n[1], n[2], 0.f);

		if (ind.texcoord_index >= 0)
		{
			const float *t = &attrib.texcoords[ind.texcoord_index * 2];
			verts[i].texcoord = glm::vec2(t[0], t[1]);
		}

		tris[i] = i;
	};

	//Applies the .obj data to our Geometry class so it can be drawn
	Geometry retval = makeGeometry(verts, vsize, tris, vsize);

	//Clear out data from the .obj
	delete[] verts;
	delete[] tris;

	return retval;
}

Texture makeTexture(unsigned width, unsigned height, unsigned format, const unsigned char *pixels)
{
	Texture retval = { 0, width, height, format };

	glGenTextures(1, &retval.handle);
	glBindTexture(GL_TEXTURE_2D, retval.handle);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	return retval;
}

Texture makeTextureF(unsigned square, const float *pixels)
{
	Texture retval = { 0, square, square, GL_RED };

	glGenTextures(1, &retval.handle);
	glBindTexture(GL_TEXTURE_2D, retval.handle);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, square, square, 0, GL_RED, GL_FLOAT, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);

	return retval;
}

void freeTexture(Texture &t)
{
	glDeleteTextures(1, &t.handle);
	t = { 0, 0, 0, 0 };
}

void drawPhong(const Shader &s, const Geometry &g, const float M[16], const float V[16], const float P[16])
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(s.handle);
	glBindVertexArray(g.vao);

	glUniformMatrix4fv(0, 1, GL_FALSE, P);
	glUniformMatrix4fv(1, 1, GL_FALSE, V);
	glUniformMatrix4fv(2, 1, GL_FALSE, M);

	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
}