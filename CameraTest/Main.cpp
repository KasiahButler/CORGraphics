#include "crenderutils.h"
#include "window.h"
#include "vertex.h"
#include "gallery.h"
#include "procgen.h"
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"
// This is a branch Test

int main()
{
	Window window;
	window.init(1280, 720);

	glm::mat4 proj = glm::perspective(45.f, 16 / 9.f, 1.f, 100.f);
	glm::mat4 view = glm::lookAt(glm::vec3(5.f, 5.f, 5.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));

	glm::mat4 model;

	Geometry geo = loadOBJ("../res/models/cube.obj");
	Shader shader = loadShader("../res/shaders/phongVert.txt", "../res/shaders/phongFrag.txt");

	float time = 0;

	while (window.step())
	{
		time += 0.016f;
		glm::mat4 model = glm::rotate(time, glm::normalize(glm::vec3(0, 1, 1)));
		drawPhong(shader, geo, glm::value_ptr(model), glm::value_ptr(view), glm::value_ptr(proj));
	}

	window.term();
	return 0;
}