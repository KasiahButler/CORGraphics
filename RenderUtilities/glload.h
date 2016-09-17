#pragma once
#include "crenderutils.h"

Shader loadShader(const char *vpath, const char *fpath);
Geometry loadOBJ(const char *path);
Texture loadTexture(const char *path);