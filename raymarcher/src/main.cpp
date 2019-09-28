#include <iostream>

#include <chrono>

#include "Image.h"
#include "Raymarcher.h"
#include "Window.h"

int main() {
	const int width  = 1185;
	const int height = 500;

	Window window(GetConsoleWindow());
	window.SetPosAndSize(0, 0, width + 50, height + 50);

	Image framebuffer(width/4, height/4);

	Raymarcher raymarcher;
	framebuffer.CreateBitmap();

	auto startTime   = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
	float t          = 0.0f;

	while (GetKeyState(VK_ESCAPE) != 0) {
		currentTime = std::chrono::high_resolution_clock::now();
		t = float(std::chrono::duration_cast<std::chrono::milliseconds>((currentTime - startTime)).count()) / 1000.f;

		raymarcher.SetTime(t);
		raymarcher.RenderOnTarget(framebuffer);
		framebuffer.UpdateBitmap();

		window.DrawImage(framebuffer, 0, 0, 4);
	}

	return 0;
}