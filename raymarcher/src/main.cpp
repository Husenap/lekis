#include <iostream>

#include <chrono>

#include "Image.h"
#include "Raymarcher.h"
#include "Window.h"

int main() {
	const int width  = 1185;
	const int height = 500;
	const int scale  = 4;

	Window window(GetConsoleWindow());
	window.SetPosAndSize(0, 0, width, height);

	Image framebuffer(width/scale, height/scale);

	Raymarcher raymarcher;
	framebuffer.CreateBitmap();

	auto startTime   = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
	float t          = 0.0f;

	while (!GetAsyncKeyState(VK_ESCAPE)) {
		currentTime = std::chrono::high_resolution_clock::now();
		t = float(std::chrono::duration_cast<std::chrono::milliseconds>((currentTime - startTime)).count()) / 1000.f;

		raymarcher.SetTime(t);
		raymarcher.RenderOnTarget(framebuffer);
		framebuffer.UpdateBitmap();

		window.DrawImage(framebuffer, 0, 0, scale);
	}

	return 0;
}