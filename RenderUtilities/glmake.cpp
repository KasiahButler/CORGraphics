#include "glmake.h"

#define GLEW_STATIC

#include "gldecs.h"
#include "GLEW\glew.h"
#include "GLM\gtc\noise.hpp"

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
	glEnableVertexAttribArray(0); //Position
	glEnableVertexAttribArray(1); //Normal
	glEnableVertexAttribArray(2); //Color
	glEnableVertexAttribArray(3); //TexCoord

						 //Index of Attribut, # of Elements, Type, Normalized, Enumerator
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

Shader makeShader(const char * vsource, const char * fsource, bool depth, bool add, bool face)
{
	glog("TODO", "Find a way to implement state management.");

	Shader retVal = { 0, depth, add, face };

	//Create all the variables
	retVal.handle = glCreateProgram();
	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);

	//Initialize all of the Variables
	glShaderSource(vs, 1, &vsource, 0);
	glShaderSource(fs, 1, &fsource, 0);

	//Compile the Shaders
	glCompileShader(vs);
	glCompileShader(fs);

	//Link all Shaders into a single Program
	glAttachShader(retVal.handle, vs);
	glAttachShader(retVal.handle, fs);
	glog_glLinkProgram(retVal.handle);

	//Delete out the Shaders once they are linked
	glDeleteShader(vs);
	glDeleteShader(fs);

	return retVal;
}

void freeShader(Shader &shader)
{
	glDeleteProgram(shader.handle);
	shader.handle = 0;
}

struct Texture makeTexture(unsigned width, unsigned height, unsigned channel, const void *pixels, bool isFloat)
{
	GLenum eformat = GL_RGBA;
	GLenum iformat = isFloat ? GL_RGBA32F : eformat;
	switch(channel)
	{
	case 0: eformat = GL_DEPTH_COMPONENT; iformat = GL_DEPTH24_STENCIL8; break;
	case 1: eformat = GL_RED; iformat = isFloat ? GL_R32F : eformat; break;
	case 2: eformat = GL_RG; iformat = isFloat ? GL_RG32F : eformat; break;
	case 3: eformat = GL_RGB; iformat = isFloat ? GL_RGB32F : eformat; break;
	case 4: eformat = GL_RGBA; iformat = isFloat ? GL_RGBA32F : eformat; break;
	default: glog("ERROR", "Channels must be 0-4");
	}

	Texture retval = { 0, width, height, channel };

	glGenTextures(1, &retval.handle);
	glBindTexture(GL_TEXTURE_2D, retval.handle);

	glTexImage2D(GL_TEXTURE_2D, 0, iformat, width, height, 0, eformat, isFloat ? GL_FLOAT : GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	return retval;
}

Texture makeTextureF(unsigned square, const float *pixels)
{
	glog("TODO", "Deprecate this.");

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

Framebuffer makeFramebuffer(unsigned width, unsigned height, unsigned nColors, bool *isFloat, int *channels)
{
	glog("TODO", "Find way to implement state management.");
	glog("TODO", "Better implementation of depth buffer.");
	glog("TODO", "Provide more options");

	Framebuffer retval = { 0, width, height, nColors };

	glGenFramebuffers(1, &retval.handle);
	glBindFramebuffer(GL_FRAMEBUFFER, retval.handle);

	retval.depth = makeTexture(width, height, 0, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, retval.depth.handle, 0);

	const GLenum attachments[8] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3,
		GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5, GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7 };

	for (int i = 0; i < nColors && i < 8; ++i)
	{
		retval.colors[i] = makeTexture(width, height, channels && channels[i] != 0 ? channels[i] : 4, 0, isFloat ? isFloat[i] : false);
		glFramebufferTexture(GL_FRAMEBUFFER, attachments[i], retval.colors[i].handle, 0);
	}

	glDrawBuffers(nColors, attachments);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return retval;
}

void freeFramebuffer(Framebuffer & fb)
{
	for (unsigned i = 0; i < fb.nColors; ++i)
	{
		freeTexture(fb.colors[i]);
	}

	glDeleteFramebuffers(1, &fb.handle);
	fb = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
}