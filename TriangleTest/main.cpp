#include "crenderutils.h"
#include "window.h"
#include "vertex.h"
#include "gallery.h"
// This is a branch Test

int main()
{
	Window window;
	Gallery gallery;
	window.init();
	gallery.init();

	gallery.loadShader("BASIC", "../res/shaders/simplevert.txt", "../res/shaders/simplefrag.txt");
	gallery.loadObject("SPHERE", "../res/models/sphere.obj");

	while (window.step())
	{
		draw(gallery.getShader("BASIC"), gallery.getObject("SPHERE"));
	}

	gallery.term();
	window.term();
	return 0;
}