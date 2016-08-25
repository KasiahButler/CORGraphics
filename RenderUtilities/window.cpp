#include "GLFW\glfw3.h"
#include "window.h"
#include <cstring>

bool Window::init(int a_width = 800, int a_height = 600, char *a_title = "Generic Window")
{
	width = a_width;
	height = a_height;
	strcpy_s(title, 64, a_title);

	glfwInit();
	winHandle = glfwCreateWindow(width, height, title, nullptr, nullptr);

	glfwMakeContextCurrent(winHandle);

	isInit = true;

	return true;
}

bool Window::step()
{
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