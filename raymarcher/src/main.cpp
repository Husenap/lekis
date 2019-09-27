#include <iostream>

#include <ctime>

#include "Image.h"
#include "Raymarcher.h"
#include "Window.h"

int main() {
	const int width  = 1185/2;
	const int height = 500/2;

	Window window(GetConsoleWindow());
	window.SetPosAndSize(0, 0, width + 50, height + 50);

	Image framebuffer(width, height);

	Raymarcher raymarcher;
	framebuffer.CreateBitmap();

	time_t startTime = time(nullptr);
	time_t currentTime = time(nullptr);
	float t         = 0.0f;

	while (GetKeyState(VK_ESCAPE) != 0) {
		currentTime = time(nullptr);
		t           = float(currentTime - startTime) / 1.f;

		raymarcher.SetTime(t);
		raymarcher.RenderOnTarget(framebuffer);
		framebuffer.UpdateBitmap();

		window.DrawImage(framebuffer, 0, 0);
	}

	return 0;
}