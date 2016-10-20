//#pragma once
//#include <string>
//#include <map>
//
//#include "crenderutils.h"
//
//// Render Object : A thing that we render
//// Shader Program : Pipeline of Shader Scripts that divide and fill the screen
//
//class Gallery
//{
//	std::map<std::string, Geometry> objects;
//	std::map<std::string, Shader>   shaders;
//
//public:
//	bool makeShader(const char* name, const char* vsource, const char *fsource);
//	bool loadShader(const char* name, const char* vpath, const char *fpath);
//
//	bool makeObject(const char*name, const Vertex *verts, size_t vsize, const unsigned *tris, size_t tsize);
//	bool loadObject(const char *name, const char *path);
//
//	const Geometry &getObject(const char *name);
//	const Shader &getShader(const char *name);
//
//	bool init();
//	bool term();
//};