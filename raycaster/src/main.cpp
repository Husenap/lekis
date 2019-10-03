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

const float maxDepth       = 16.0f;
const float sampleInterval = 0.0125f;

Map map;
Player player;

void UpdateGame(float dt) {
	if (GetAsyncKeyState(VK_UP)) {
		player.pos += lks::vec3::FromAngle(player.lookAngle) * player.speed * dt;
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		player.pos -= lks::vec3::FromAngle(player.lookAngle) * player.speed * dt;
	}
	if (GetAsyncKeyState(VK_LEFT)) {
		player.lookAngle -= 0.5f * player.speed * dt;
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		player.lookAngle += 0.5f * player.speed * dt;
	}
	return;
}

void RenderGame(lks::Image& framebuffer) {
	auto& pixels = framebuffer.Pixels();
	int width    = framebuffer.GetWidth();
	int height   = framebuffer.GetHeight();

	for (int x = 0; x < width; ++x) {
		float rayAngle = (player.lookAngle - 0.5f * player.fov) + (x / float(width)) * player.fov;
		float rayLen   = 0.0f;

		lks::vec3 rayDir = lks::vec3::FromAngle(rayAngle);

		bool hitWall = false;
		while (!hitWall && rayLen < maxDepth) {
			rayLen += sampleInterval;

			lks::vec3 samplePos = player.pos + rayDir * rayLen;

			int sampleX = (int)samplePos.x;
			int sampleY = (int)samplePos.y;

			if (sampleX < 0 || sampleX >= map.GetWidth() || sampleY < 0 || sampleY >= map.GetHeight()) {
				hitWall = true;
				rayLen  = maxDepth;
			} else {
				if (map[sampleY * map.GetWidth() + sampleX] == '#') {
					hitWall = true;
				}
			}
		}

		for (int y = 0; y < height; ++y) {
			int ceiling = (0.5f * height) - (height / rayLen);
			int floor   = height - ceiling;

			float c;

			if (y < ceiling) {
				c = 0.0f;
			} else if (y > ceiling && y <= floor) {
				c = 1.0f * (1.0f - rayLen / maxDepth);
			} else {
				c = 0.3f;
			}

			pixels[y * width + x] = ToColor(lks::vec3{1.0f, 1.0f, 0.0f} * c);
		}
	}
}

int main() {

	const int width  = 2048;
	const int height = 512;

	Bitmap bitmap("assets/mina.bmp");

	lks::FPSCounter fpsCounter(100);

	lks::Window window(GetConsoleWindow());
	window.SetPosAndSize(100, 100, width, height);
	window.SetFont(SYSTEM_FIXED_FONT);

	lks::Image framebuffer(width, height);

	//framebuffer.Pixels() = bitmap.GetPixels();
	framebuffer.CreateBitmap();

	auto startTime   = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
	float t          = 0.f;
	float dt         = 0.f;

	player.pos = {8.0f, 8.0f, 0.0f};

	while (!GetAsyncKeyState(VK_ESCAPE)) {
		dt = float(std::chrono::duration_cast<std::chrono::nanoseconds>(
		               (std::chrono::high_resolution_clock::now() - currentTime))
		               .count()) /
		     1000000000.f;
		currentTime = std::chrono::high_resolution_clock::now();
		t += dt;

		fpsCounter.PushTime(dt);

		UpdateGame(dt);
		RenderGame(framebuffer);

		framebuffer.UpdateBitmap();

		window.SetRenderTarget(framebuffer);

		window.RenderText(("fps: " + std::to_string(fpsCounter.GetFPS())).c_str(), 1, 1, 0x009d5dfc);
		window.RenderText(map.ToString(player), 1, 50, 0x0096c5f9);

		window.Present();

		std::this_thread::yield();
	}

	return 0;
}
