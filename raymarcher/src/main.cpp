#include <iostream>

#include <chrono>
#include <string>
#include <thread>
#include <vector>

#include "util/FPSCounter.h"
#include "rendering/Image.h"
#include "rendering/Window.h"
#include "Raymarcher.h"

int main() {
	const int width  = 1185 / 4;
	const int height = 500 / 4;

	lks::FPSCounter fpsCounter(100);

	lks::Window window(GetConsoleWindow());
	window.SetPosAndSize(100, 100, width, height);

	lks::Image framebuffer(width, height);

	Raymarcher raymarcher;
	framebuffer.CreateBitmap();

	auto startTime   = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
	float t          = 0.f;
	float dt         = 0.f;

	while (!GetAsyncKeyState(VK_ESCAPE)) {
		dt = float(std::chrono::duration_cast<std::chrono::nanoseconds>(
		               (std::chrono::high_resolution_clock::now() - currentTime))
		               .count()) /
		     1000000000.f;
		currentTime = std::chrono::high_resolution_clock::now();
		t += dt;

		fpsCounter.PushTime(dt);

		raymarcher.SetTime(t);
		raymarcher.RenderOnTarget(framebuffer);
		framebuffer.UpdateBitmap();

		window.SetRenderTarget(framebuffer);
		window.RenderText(("fps: " + std::to_string(fpsCounter.GetFPS())).c_str(), 1, 1, 0x00ff9900);
		window.Present();

		std::this_thread::yield();
	}

	return 0;
}