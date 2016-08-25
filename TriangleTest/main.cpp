#include "crenderutils.h"
#include "window.h"

// This is a branch Test

int main()
{
	Window window;
	window.init();

	while (window.step());

	window.term();

	return 0;
}