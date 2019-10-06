#include <math.h>
#include <chrono>
#include <execution>
#include <string>
#include <thread>

#include "Map.h"
#include "Player.h"
#include "math/Vec3.h"
#include "rendering/Image.h"
#include "rendering/Window.h"
#include "util/FPSCounter.h"
#include "Bitmap.h"
#include "Raycaster.h"


void RenderGame(lks::Image& framebuffer) {
}

int main() {

	//const int width  = 80;
	//const int height = 60;
	const int width  = 1920;
	const int height = 1080;

	lks::FPSCounter fpsCounter(100);

	lks::Window window(GetConsoleWindow());
	window.SetPosAndSize(100, 100, width, height);
	window.SetFont(SYSTEM_FIXED_FONT);

	lks::Image framebuffer(width, height);

	framebuffer.CreateBitmap();

	Raycaster raycaster(framebuffer);

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

		raycaster.UpdateScene(dt);
		raycaster.RenderScene();

		window.SetRenderTarget(framebuffer);

		window.RenderText(("fps: " + std::to_string(fpsCounter.GetFPS())).c_str(), 1, 1, 0x009d5dfc);
		window.RenderText(raycaster.GetMapString(), 1, 50, 0x0096c5f9);
		window.RenderText("look angle:" + std::to_string(raycaster.GetPlayer().lookAngle * (180 / lks::PI)), 1, 500, 0x0032cd32);

		window.Present();

		std::this_thread::yield();
	}

	return 0;
}
