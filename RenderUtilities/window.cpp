#define GLEW_STATIC

#include "GLEW\glew.h"
#include "GLFW\glfw3.h"
#include "window.h"
#include <cstring>

bool Window::init(int a_width, int a_height, char *a_title)
{
	width = a_width;
	height = a_height;
	strcpy_s(title, 64, a_title);

	glfwInit();
	winHandle = glfwCreateWindow(width, height, title, nullptr, nullptr);

	glfwMakeContextCurrent(winHandle);

	isInit = true;

	glewExperimental = true;
	glewInit();
	glClearColor(0.2f, 1.0f, 0.5f, 1.0f);

	return true;
}

bool Window::step()
{
	if (!isInit) return false;

	glClear(GL_COLOR_BUFFER_BIT);

	glfwPollEvents();
	glfwSwapBuffers(winHandle);

	return !glfwWindowShouldClose(winHandle);
}

bool Window::term()
{
	glfwDestroyWindow(winHandle);
	glfwTerminate();
	
	winHandle = nullptr;
	isInit = false;

	return true;
}