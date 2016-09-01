#include "crenderutils.h"
#include "window.h"
#include "vertex.h"
#include "gallery.h"
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"
// This is a branch Test

int main()
{
	Window window;
	Gallery gallery;
	window.init();
	gallery.init();

	float time = 0;
	float IDENTITY[16] = {1,0,0,0,
						  0,1,0,0,
						  0,0,1,0,
						  0,0,0,1};

	glm::mat4 proj, view, model, model2;

	proj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
	view = glm::lookAt(glm::vec3(5.f, 5.f, 5.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	model = glm::scale(glm::vec3(1.23f, 1.5f, 1.5f));
	model2 = glm::scale(glm::vec3(1.43f, 1.7f, 1.7f));
	

	gallery.loadShader("CAMERA", "../res/shaders/cameravert.txt", "../res/shaders/camerafrag.txt");
	gallery.loadObject("CUBE", "../res/models/cube.obj");

	while (window.step())
	{

		time += .022f;

		model2 = glm::rotate(time, glm::vec3(0, 1, 0));

		Ndraw(gallery.getShader("CAMERA"), gallery.getObject("CUBE"), glm::value_ptr(model * glm::translate(glm::vec3(1, 1, 1))), glm::value_ptr(view), glm::value_ptr(proj));
		Ndraw(gallery.getShader("CAMERA"), gallery.getObject("CUBE"), glm::value_ptr(model2 * glm::translate(glm::vec3(1, 0, 1))), glm::value_ptr(view), glm::value_ptr(proj));
	}

	gallery.term();
	window.term();
	return 0;
}