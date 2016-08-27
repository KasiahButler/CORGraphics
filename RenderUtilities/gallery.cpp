#include "gallery.h"

bool Gallery::makeShader(const char * name, const char * vsource, const char * fsource)
{
	//Functionality to check if name is already being used needs to be added
	shaders[name] = ::makeShader(vsource, fsource);
	return true;
}

bool Gallery::loadShader(const char * name, const char * vpath, const char * fpath)
{
	shaders[name] = ::loadShader(vpath, fpath);
	return true;
}

bool Gallery::makeObject(const char * name, const Vertex * verts, size_t vsize, const unsigned * tris, size_t tsize)
{
	objects[name] = makeGeometry(verts, vsize, tris, tsize);
	return true;
}

bool Gallery::loadObject(const char * name, const char * path)
{
	objects[name] = loadOBJ(path);
	return true;
}

const Geometry &Gallery::getObject(const char * name)
{
	return objects[name];
}

const Shader &Gallery::getShader(const char * name)
{
	return shaders[name];
}

bool Gallery::init()
{
	return true;
}

bool Gallery::term()
{
	for each(auto shader in shaders) { freeShader(shader.second); }
	for each(auto object in objects) { freeGeometry(object.second); }

	return true;
}
