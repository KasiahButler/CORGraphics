#pragma once
#pragma once
#include "vertex.h"
#include "crenderutils.h"


struct Geometry makeGeometry(const struct Vertex *verts, size_t vsize, const unsigned int *tris, size_t tsize);
void freeGeometry(Geometry &);

struct Shader makeShader(const char *vsource, const char *fsource, bool depth = true, bool add = false, bool face = true);
void freeShader(Shader &);

struct Texture makeTexture(unsigned width, unsigned height, unsigned channel, const void *pixels, const bool isFloat = false);
struct Texture makeTextureF(unsigned square, const float *pixels);
void freeTexture(Texture &);

struct Framebuffer makeFramebuffer(unsigned width, unsigned height, unsigned nColors, bool *isFloat = nullptr, int *channels = nullptr);
void freeFramebuffer(Framebuffer &);