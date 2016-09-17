#pragma once

#include "globjs.h"
#include "glload.h"
#include "glmake.h"
#include "gldraw.h"

#include "vertex.h"
#include "window.h"

//#include "globjects.h"
//
//
//Geometry makeGeometry(const Vertex *verts, size_t vsize, const unsigned int *tris, size_t tsize);
//void freeGeometry(Geometry &);
//
//Shader makeShader(const char *vsource, const char *fsource);
//Shader loadShader(const char *vpath, const char *fpath);
//void freeShader(Shader &);
//
//void draw(const Shader &, const Geometry &);
//void draw(const Shader &s, const Geometry &g, const float M[16], const float V[16], const float P[16]);
//
//Geometry loadOBJ(const char *path);
//
//Texture makeTexture(unsigned width, unsigned height, unsigned format, const unsigned char *pixels);
//Texture makeTextureF(unsigned square, const float *pixels);
//Texture loadTexture(const char *path);
//void freeTexture(Texture &t);
//
//void drawPhong(const Shader &s, const Geometry &g, const float M[16], const float V[16], const float P[16]);
//void drawPhong(const Shader &s, const Geometry &g, const float M[16], const float V[16], const float P[16], const Texture *T, unsigned t_count);
//
//Framebuffer makeFramebuffer(unsigned width, unsigned height, unsigned nColors);
//void clearFramebuffer(const Framebuffer &);
//void freeFramebuffer(Framebuffer &fb);
//
//void drawFB(const Shader &s, const Geometry &g, const Framebuffer &f, const float M[16], const float V[16], const float P[16], const Texture *T, unsigned t_count);