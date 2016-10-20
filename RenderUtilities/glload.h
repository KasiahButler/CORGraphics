#pragma once
#include "crenderutils.h"

Shader loadShader(const char *vpath, const char *fpath, bool depth = true, bool add = false, bool face = true);
Geometry loadOBJ(const char *path);
Texture loadTexture(const char *path);