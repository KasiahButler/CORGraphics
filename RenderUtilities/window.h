#pragma once

class Window
{
private:
	int width, height;
	char title[64];
	bool isInit = false; //Optional, could set winHandle ptr to Null and just check for Null

	//Forward Declaration, should be used when declaring pointers
	struct GLFWwindow *winHandle = nullptr;

public:
	// Could add functions to check isInit, Width/Height of Screen, Title etc.

	//Use bools so that we know if the window Initializes, Updates, and Terminates properly
	bool init(int a_width = 800, int a_height = 600, char *a_title = "Generic Window"); // Alternatives: Setup, Start etc.
	bool step(); // Update, Refresh etc.
	bool term(); // Kill, Terminate etc.
};