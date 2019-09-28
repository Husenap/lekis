#include <iostream>

#include <chrono>
#include <thread>
#include <string>

#include "Image.h"
#include "Raymarcher.h"
#include "Window.h"

int main() {
	const int width  = 1185;
	const int height = 500;

	Window window(GetConsoleWindow());
	window.SetPosAndSize(0, 0, width, height);

	Image framebuffer(width, height);

	Raymarcher raymarcher;
	framebuffer.CreateBitmap();

	auto startTime   = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
	float t          = 0.f;
	float dt         = 0.f;

	while (!GetAsyncKeyState(VK_ESCAPE)) {
		dt = float(std::chrono::duration_cast<std::chrono::milliseconds>((std::chrono::high_resolution_clock::now() - currentTime)).count()) / 1000.f;
		currentTime = std::chrono::high_resolution_clock::now();
		t += dt;

		raymarcher.SetTime(t);
		raymarcher.RenderOnTarget(framebuffer);
		framebuffer.UpdateBitmap();

		window.SetRenderTarget(framebuffer);
		window.RenderText(("fps: " + std::to_string(1.f / dt)).c_str(), 1, 1, 0x00ff9900);
		window.Present();

		std::this_thread::yield();
	}

	return 0;
}