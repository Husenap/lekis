#include <iostream>

#include "Image.h"
#include "Raymarcher.h"
#include "Window.h"

int main() {
	const int width  = 1185;
	const int height = 500;

	Window window(GetConsoleWindow());
	window.SetPosAndSize(0, 0, width + 50, height + 50);

	Image framebuffer(width, height);

	Raymarcher raymarcher;
	raymarcher.RenderOnTarget(framebuffer);
	framebuffer.CreateBitmap();

	window.DrawImage(framebuffer, 0, 0);

	std::cin.ignore();

	return 0;
}