#include "glload.h"
#include "glmake.h"
#include "gldecs.h"

#include <fstream>
#include <istream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "STB\stb_image.h"

#include "crenderutils.h"
#include "vertex.h"

std::string fileToString(const char *filePath)
{
	/*String Method*/
	std::ifstream shaderFile{ filePath };
	std::string shaderContents{ std::istreambuf_iterator<char>(shaderFile), std::istreambuf_iterator<char>() };

	/*C++ ifstream method*/
	//unsigned fileSize = 0;

	//std::ifstream shaderFile(filePath, std::ios::binary | std::ios::ate);

	//fileSize = shaderFile.tellg();

	//char *shaderContents = (char*)(malloc((fileSize + 1) * sizeof(char)));

	//shaderFile.seekg(0, shaderFile.beg);
	//shaderFile.read(shaderContents, fileSize);
	
	/*C style FILE method*/
	//FILE *shaderFile;
	//fopen_s(&shaderFile, filePath, "rb");

	//fseek(shaderFile, 0, SEEK_END);
	//fileSize = ftell(shaderFile);
	//fseek(shaderFile, 0, SEEK_SET);

	//char *shaderContents = (char*)(malloc((fileSize + 1) * sizeof(char)));

	//fread(shaderContents, fileSize, 1, shaderFile);

	//fclose(shaderFile);

	return shaderContents;
}

Shader loadShader(const char * vpath, const char * fpath)
{
	glog("Loading Shader", vpath);
	glog("Loading Shader", fpath);

	std::string vsource = fileToString(vpath);
	std::string fsource = fileToString(fpath);

	//char* vsource = fileToString(vpath);
	//char* fsource = fileToString(fpath);

	return makeShader(vsource.c_str(), fsource.c_str());

	//Shader retShader = makeShader(vsource, fsource);
	//delete[] vsource;
	//delete[] fsource;
	//return retShader;
}

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "OBJ\tiny_obj_loader.h"
#include <random>

Geometry loadOBJ(const char *path)
{
	glog("TODO", "Eliminate Redundant Vertices");

	//TinyOBJ required code for setup
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	//Sets up and confirms that an object can be loaded
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

	int vsize = shapes[0].mesh.indices.size();

	//Builds an array of Verticies and Triangles to work with based on .obj size
	Vertex   *verts = new Vertex[vsize];
	unsigned *tris = new unsigned[vsize];

	//Breaks up the .obj info so that it is in a format we can use
	for (int i = 0; i < vsize; ++i)
	{
		auto ind = shapes[0].mesh.indices[i];

		const float *n = &attrib.normals[ind.normal_index * 3];
		const float *p = &attrib.vertices[ind.vertex_index * 3];

		verts[i].position = glm::vec4(p[0], p[1], p[2], 1.f);
		verts[i].normal = glm::vec4(n[0], n[1], n[2], 0.f);

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

Texture loadTexture(const char * path)
{
	glog("loading Texture", path);

	int w, h, f;
	unsigned char *p;

	Texture retval = { 0,0,0,0 };

	stbi_set_flip_vertically_on_load(true); // DirectX or OpenGL
	p = stbi_load(path, &w, &h, &f, STBI_default);

	if (!p) return retval;

	switch (f)
	{
	case STBI_grey: f = GL_RED;
		break;
	case STBI_grey_alpha: f = GL_RG;
		break;
	case STBI_rgb: f = GL_RGB;
		break;
	case STBI_rgb_alpha: f = GL_RGBA;
		break;
	}

	retval = makeTexture(w, h, f, p);
	stbi_image_free(p);
	return retval;
}
