//#define GLEW_STATIC
//
//#include "gldecs.h"
//#include "GLEW\glew.h"
//#include "GLM\gtc\noise.hpp"
//
//#define STB_IMAGE_IMPLEMENTATION
//#include "STB\stb_image.h"
//
//#include "crenderutils.h"
//#include "vertex.h"
//
//#include <fstream>
//#include <cstdio>
//
//Geometry makeGeometry(const Vertex *verts, size_t vsize, const unsigned int *tris, size_t tsize)
//{
//	Geometry retVal;
//	retVal.size = tsize;
//
//	
//	//Define all the Variables
//	glGenBuffers(1, &retVal.vbo);
//	glGenBuffers(1, &retVal.ibo);
//	glGenVertexArrays(1, &retVal.vao);
//
//	//Scope all the variables
//	glBindVertexArray(retVal.vao);
//	glBindBuffer(GL_ARRAY_BUFFER, retVal.vbo);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retVal.ibo);
//
//	//Initialize the Variables
//	glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(Vertex), verts, GL_STATIC_DRAW);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tsize * sizeof(unsigned), tris, GL_STATIC_DRAW);
//
//	//Attributes
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//	glEnableVertexAttribArray(2);
//	glEnableVertexAttribArray(3);
//
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::POSITION);
//	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::COLOR);
//	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::NORMAL);
//	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::TEXCOORD);
//	
//
//	//Unscope the Variables
//	glBindVertexArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//	return retVal;
//}
//
//void freeGeometry(Geometry &geo)
//{
//	glDeleteBuffers(1, &geo.vbo);
//	glDeleteBuffers(1, &geo.ibo);
//	glDeleteVertexArrays(1, &geo.vao);
//	geo = { 0, 0, 0, 0 };
//}
//
//Shader makeShader(const char * vsource, const char * fsource)
//{
//	Shader retVal;
//
//	//Create all the variables
//	retVal.handle = glCreateProgram();
//
//	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
//	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);
//
//	//Initialize all of the Variables
//	glShaderSource(vs, 1, &vsource, 0);
//	glShaderSource(fs, 1, &fsource, 0);
//
//	//Compile the Shaders
//	glCompileShader(vs);
//	glCompileShader(fs);
//
//	//Link all Shaders into a single Program
//	glAttachShader(retVal.handle, vs);
//	glAttachShader(retVal.handle, fs);
//	glLinkProgram(retVal.handle);
//
//	//Delete out the Shaders once they are linked
//	glDeleteShader(vs);
//	glDeleteShader(fs);
//
//	return retVal;
//}
//
////Shit doesn't work, still getting garbage data, fix later, use fileToString for the time being
////char *loadTextFile(const char *fileLocation)
////{
////	FILE *shaderFile = nullptr;
////
////	fopen_s(&shaderFile, fileLocation, "r");
////
////	fseek(shaderFile, 0, SEEK_END);
////	unsigned fileSize = ftell(shaderFile);
////
////	char* shader = new char[fileSize];
////
////	rewind(shaderFile);
////	fread(shader, sizeof(char), fileSize, shaderFile);
////
////	return shader;
////}
//
//#include <fstream>
//#include <istream>
//#include <string>
//
//std::string fileToString(const char *filePath)
//{
//	std::ifstream shaderFile{ filePath };
//	std::string shaderContents{ std::istreambuf_iterator<char>(shaderFile), std::istreambuf_iterator<char>() };
//	return shaderContents;
//}
//
//Shader loadShader(const char * vpath, const char * fpath)
//{
//	std::string vsource = fileToString(vpath);
//	std::string fsource = fileToString(fpath);
//
//	return makeShader(vsource.c_str(), fsource.c_str());
//}
//
//void freeShader(Shader &shader)
//{
//	glDeleteProgram(shader.handle);
//	shader.handle = 0;
//}
//
//void draw(const Shader &shader, const Geometry &geometry)
//{
//	//Uses the Shader Program created at handle
//	glUseProgram(shader.handle);
//	
//	//Binding VAO also binds IBO (Tri) and VBO (Verts)
//	glBindVertexArray(geometry.vao);
//	
//	//Draw the vertices that are currently bound using array of indices
//	//If IBO is bound, don't need to proved Indicies (NULL in this case)
//	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, NULL);
//}
//
//void draw(const Shader &s, const Geometry &g, const float M[16], const float V[16], const float P[16])
//{
//	glEnable(GL_CULL_FACE);
//	//glEnable(GL_DEPTH_TEST);
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//	glUseProgram(s.handle);
//	glBindVertexArray(g.vao);
//
//	glUniformMatrix4fv(0, 1, GL_FALSE, P);
//	glUniformMatrix4fv(1, 1, GL_FALSE, V);
//	glUniformMatrix4fv(2, 1, GL_FALSE, M);
//
//	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
//}
//
//#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
//#include "OBJ\tiny_obj_loader.h"
//#include <random>
//
//Geometry loadOBJ(const char *path)
//{
//	//TinyOBJ required code for setup
//	tinyobj::attrib_t attrib;
//	std::vector<tinyobj::shape_t> shapes;
//	std::vector<tinyobj::material_t> materials;
//	std::string err;
//
//	//Sets up and confirms that an object can be loaded
//	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);
//
//	int vsize = shapes[0].mesh.indices.size();
//
//	//Builds an array of Verticies and Triangles to work with based on .obj size
//	Vertex   *verts = new Vertex[vsize];
//	unsigned *tris = new unsigned[vsize];
//
//	//Breaks up the .obj info so that it is in a format we can use
//	for (int i = 0; i < vsize; ++i)
//	{
//		auto ind = shapes[0].mesh.indices[i];
//
//		const float *n =   &attrib.normals[ind.normal_index * 3];
//		const float *p =  &attrib.vertices[ind.vertex_index * 3];
//
//		verts[i].position = glm::vec4(p[0], p[1], p[2], 1.f);
//		verts[i].normal =   glm::vec4(n[0], n[1], n[2], 0.f);
//
//		if (ind.texcoord_index >= 0)
//		{
//			const float *t = &attrib.texcoords[ind.texcoord_index * 2];
//			verts[i].texcoord = glm::vec2(t[0], t[1]);
//		}
//
//		tris[i] = i;
//	};
//
//	//Applies the .obj data to our Geometry class so it can be drawn
//	Geometry retval = makeGeometry(verts, vsize, tris, vsize);
//
//	//Clear out data from the .obj
//	delete[] verts;
//	delete[] tris;
//
//	return retval;
//}
//
//Texture makeTexture(unsigned width, unsigned height, unsigned format, const unsigned char *pixels)
//{
//	Texture retval = { 0, width, height, format };
//
//	glGenTextures(1, &retval.handle);
//	glBindTexture(GL_TEXTURE_2D, retval.handle);
//
//	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	return retval;
//}
//
//Texture makeTextureF(unsigned square, const float *pixels)
//{
//	Texture retval = { 0, square, square, GL_RED };
//
//	glGenTextures(1, &retval.handle);
//	glBindTexture(GL_TEXTURE_2D, retval.handle);
//
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, square, square, 0, GL_RED, GL_FLOAT, pixels);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	return retval;
//}
//
//Texture loadTexture(const char * path)
//{
//	glog("loading Texture", "path");
//	int w, h, f;
//	unsigned char *p;
//
//	Texture retval = { 0,0,0,0 };
//
//	stbi_set_flip_vertically_on_load(true); // DirectX or OpenGL
//	p = stbi_load(path, &w, &h, &f, STBI_default);
//
//	if (!p) return retval;
//
//	switch (f)
//	{
//	case STBI_grey: f = GL_RED; 
//		break;
//	case STBI_grey_alpha: f = GL_RG;   
//		break;
//	case STBI_rgb: f = GL_RGB;  
//		break;
//	case STBI_rgb_alpha: f = GL_RGBA; 
//		break;
//	}
//
//	retval = makeTexture(w, h, f, p);
//	stbi_image_free(p);
//	return retval;
//}
//
//void freeTexture(Texture &t)
//{
//	glDeleteTextures(1, &t.handle);
//	t = { 0, 0, 0, 0 };
//}
//
//void drawPhong(const Shader &s, const Geometry &g, const float M[16], const float V[16], const float P[16])
//{
//	glEnable(GL_CULL_FACE);
//	glEnable(GL_DEPTH_TEST);
//
//	glUseProgram(s.handle);
//	glBindVertexArray(g.vao);
//
//	glUniformMatrix4fv(0, 1, GL_FALSE, P);
//	glUniformMatrix4fv(1, 1, GL_FALSE, V);
//	glUniformMatrix4fv(2, 1, GL_FALSE, M);
//
//	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
//}
//
//void drawPhong(const Shader &s, const Geometry &g, const float M[16], const float V[16], const float P[16], const Texture *T, unsigned t_count)
//{
//	glEnable(GL_CULL_FACE);
//	glEnable(GL_DEPTH_TEST);
//
//	glUseProgram(s.handle);
//	glBindVertexArray(g.vao);
//
//	glUniformMatrix4fv(0, 1, GL_FALSE, P);
//	glUniformMatrix4fv(1, 1, GL_FALSE, V);
//	glUniformMatrix4fv(2, 1, GL_FALSE, M);
//
//	int i = 0;
//	for (; i < t_count; ++i)
//	{
//		glActiveTexture(GL_TEXTURE + i);
//		glBindTexture(GL_TEXTURE_2D, T[i].handle);
//		glUniform1i(3 + i, 0 + i);
//	}
//
//	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
//}
//
//Framebuffer makeFramebuffer(unsigned width, unsigned height, unsigned nColors)
//{
//	Framebuffer retval = { 0, width, height, nColors};
//
//	glGenFramebuffers(1, &retval.handle);
//	glBindFramebuffer(GL_FRAMEBUFFER, retval.handle);
//
//	retval.depth = makeTexture(width, height, GL_DEPTH_COMPONENT, 0);
//	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, retval.depth.handle, 0);
//
//	const GLenum attachments[8] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3,
//								    GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5, GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7 };
//
//	for (int i = 0; i < nColors && i < 8; ++i)
//	{
//		retval.colors[i] = makeTexture(width, height, GL_RGBA, 0);
//		glFramebufferTexture(GL_FRAMEBUFFER, attachments[i], retval.colors[i].handle, 0);
//	}
//
//	glDrawBuffers(nColors, attachments);
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	return retval;
//}
//
//void freeFramebuffer(Framebuffer & fb)
//{
//	for (unsigned i = 0; i < fb.nColors; ++i)
//	{
//		freeTexture(fb.colors[i]);
//	}
//
//	glDeleteFramebuffers(1, &fb.handle);
//	fb = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//}
//
//void clearFramebuffer(const Framebuffer &fb)
//{
//	glBindFramebuffer(GL_FRAMEBUFFER, fb.handle);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}
//
//void drawFB(const Shader & s, const Geometry & g, const Framebuffer & f, const float M[16], const float V[16], const float P[16], const Texture * T, unsigned t_count)
//{
//	glEnable(GL_CULL_FACE);
//	glEnable(GL_DEPTH_TEST);
//
//	glBindFramebuffer(GL_FRAMEBUFFER, f.handle);
//	glUseProgram(s.handle);
//	glBindVertexArray(g.vao);
//
//	glViewport(0, 0, f.width, f.height);
//
//	glUniformMatrix4fv(0, 1, GL_FALSE, P);
//	glUniformMatrix4fv(1, 1, GL_FALSE, V);
//	glUniformMatrix4fv(2, 1, GL_FALSE, M);
//
//	int i = 0;
//	for (; i < t_count; ++i)
//	{
//		glActiveTexture(GL_TEXTURE0 + i);
//		glBindTexture(GL_TEXTURE_2D, T[i].handle);
//		glUniform1i(3 + i, 0 + i);
//	}
//
//	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
//}
