#include <windows.h>
#include <algorithm>
#include <cmath>
#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

const float PI = 3.1415926535f;

const int WIDTH      = 1185;
const int HEIGHT     = 500;
const int MAX_STEPS  = 256;
const float MIN_DIST = 0.01f;
const float MAX_DIST = 20.f;

struct vec3 {
	union {
		struct {
			float x, y, z;
		};
		struct {
			float r, g, b;
		};
	};
};
static vec3 operator+(const vec3& a, const vec3& b) {
	return vec3{a.x + b.x, a.y + b.y, a.z + b.z};
}
static vec3 operator-(const vec3& a, const vec3& b) {
	return vec3{a.x - b.x, a.y - b.y, a.z - b.z};
}
static vec3 operator*(const vec3& a, const float& b) {
	return vec3{a.x * b, a.y * b, a.z * b};
}
static vec3 operator/(const vec3& a, const float& b) {
	return vec3{a.x / b, a.y / b, a.z / b};
}
float Length(const vec3& v) {
	return std::sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}
vec3 Normalize(const vec3& v) {
	return v / Length(v);
}
float Smoothstep(float low, float high, float t) {
	t = std::clamp((t - low) / (high - low), 0.0f, 1.f);
	return t * t * (3.f - 2.f * t);
}
float Saturate(float f) {
	return std::clamp(f, 0.f, 1.f);
}
int32_t ToColor(const vec3& v) {
	return (int32_t(std::clamp(v.r, 0.0f, 1.0f) * 255.f) << 16) | (int32_t(std::clamp(v.g, 0.0f, 1.0f) * 255.f) << 8) |
	       (int32_t(std::clamp(v.b, 0.0f, 1.0f) * 255.f));
}
int32_t ToColor(const float& v) {
	return ToColor(vec3{v, v, v});
}

struct Sphere {
	vec3 pos;
	float r;
};

float SphereHit(vec3 p, Sphere sphere) {
	return Length(p - sphere.pos) - sphere.r;
}


float Map(vec3 p) {
	return SphereHit(p, Sphere{{0.f, 0.f, 0.f}, 1.0f});
}

float RayMarch(vec3 ro, vec3 rd) {
	float t = 0.f;
	for (int i = 0; i < MAX_STEPS; ++i) {
		vec3 p = ro + rd * t; 

		float d = Map(p);

		if (d < MIN_DIST) {
			break;
		}

		t += d;

		if (t > MAX_DIST) {
			break;
		}
	}

	return t;
}

void DrawPixelsToBitmap(std::vector<int32_t>& pixels, int width, int height) {
	for (int i = 0; i < pixels.size(); ++i) {
		int x = i % width;
		int y = i / width;

		vec3 uv = {0.0f};
		uv.x    = ((float)x / (float)width) * 2.f - 1.f;
		uv.y    = (1.f - ((float)y / (float)height)) * 2.f - 1.f;
		uv.x *= float(WIDTH) / float(HEIGHT);

		vec3 ro = vec3{0.f, 0.f, -3.f};
		vec3 rd = Normalize(vec3{uv.x, uv.y, 0.8f});

		float d = RayMarch(ro, rd);

		vec3 col = vec3{0.0f, 0.0f, 0.0f};

		if (d < MAX_DIST){
			col = ro + rd * d;
		}

		pixels[i] = ToColor(col);
	}
}

int main() {
	HWND hConsole = GetConsoleWindow();
	SetWindowPos(hConsole, NULL, 0, 0, WIDTH + 50, HEIGHT + 50, 0);

	HDC hDC       = GetDC(hConsole);
	HDC hMemoryDC = CreateCompatibleDC(hDC);

	std::vector<int32_t> pixelData;
	pixelData.resize(WIDTH * HEIGHT);
	std::fill(pixelData.begin(), pixelData.end(), 0);

	DrawPixelsToBitmap(pixelData, WIDTH, HEIGHT);

	HBITMAP hBitmap = CreateBitmap(WIDTH, HEIGHT, 1, 32, pixelData.data());
	SelectObject(hMemoryDC, hBitmap);

	BitBlt(hDC, 0, 0, WIDTH, HEIGHT, hMemoryDC, 0, 0, SRCCOPY);

	std::cin.ignore();

	DeleteDC(hMemoryDC);
	ReleaseDC(hConsole, hDC);

	return 0;
}