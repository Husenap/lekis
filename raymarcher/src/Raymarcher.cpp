#include "Raymarcher.h"

#include <algorithm>
#include <execution>

#include "math/SDF.h"
#include "math/MathUtils.h"
#include "math/Vec3.h"

const int MAX_STEPS  = 256;
const float MIN_DIST = 0.01f;
const float MAX_DIST = 20.f;

Raymarcher::Raymarcher() {}

Raymarcher::~Raymarcher() {}

void Raymarcher::RenderOnTarget(lks::Image& framebuffer) {
	auto& pixels = framebuffer.Pixels();
	int width    = framebuffer.GetWidth();
	int height   = framebuffer.GetHeight();

	std::for_each(std::execution::par, framebuffer.Indices().begin(), framebuffer.Indices().end(), [&](int32_t i) {
		int x = i % width;
		int y = i / width;

		lks::vec3 color;
		MainImage(color, {(float)x, (float)(height - y), 0.f}, {(float)width, (float)height, 0.f});
		pixels[i] = ToColor(color);
	});
}

float Raymarcher::Map(lks::vec3 p) {
	float radius = 1.f;
	float sphere = sdSphere(p - lks::vec3{std::sinf(mTime), 0.f, 0.f}, radius);
	float box    = sdBox(p - lks::vec3{4.f, 0.f, 1.f}, {1.f, 1.f, 2.f});
	float plane  = p.y + radius;

	float d = std::fminf(sphere, plane);
	d       = std::fminf(d, box);

	return d;
}

lks::vec3 Raymarcher::CalcNormal(lks::vec3 p) {
	const lks::vec3 e = lks::vec3{1.0, -1.0, 0.0} * 0.0002f;
	const lks::vec3 xyy{e.x, e.y, e.y};
	const lks::vec3 yyx{e.y, e.y, e.x};
	const lks::vec3 yxy{e.y, e.x, e.y};
	const lks::vec3 xxx{e.x, e.x, e.x};
	return Normalize(xyy * Map(p + xyy) + yyx * Map(p + yyx) + yxy * Map(p + yxy) + xxx * Map(p + xxx));
}

float Raymarcher::RayMarch(lks::vec3 ro, lks::vec3 rd) {
	float t = 0.f;
	for (int i = 0; i < MAX_STEPS; ++i) {
		lks::vec3 p = ro + rd * t;

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

void Raymarcher::MainImage(lks::vec3& fragColor, const lks::vec3& fragCoord, const lks::vec3& resolution) {
	lks::vec3 uv = (fragCoord * 2.f - resolution) / resolution.y;

	lks::vec3 ro = {0.f, 0.f, -3.f};
	lks::vec3 rd = lks::Normalize({uv.x, uv.y, 0.8f});

	float t = RayMarch(ro, rd);

	lks::vec3 col = {0.0f, 0.0f, 0.0f};

	if (t < MAX_DIST) {
		lks::vec3 position = ro + rd * t;
		lks::vec3 normal   = CalcNormal(position);

		lks::vec3 material = {0.2f, 0.2f, 0.2f};

		lks::vec3 sunCol = {7.f, 4.5f, 3.5f};
		lks::vec3 skyCol = {0.533f, 0.808f, 0.9f};
		lks::vec3 bouCol = {0.7, 0.3, 0.2f};

		lks::vec3 sunDir = {0.65f, 0.35f, 0.2f};

		float sunDif = lks::Saturate(lks::Dot(normal, sunDir));
		float skyDif = 0.5f + 0.5f * lks::Saturate(lks::Dot(normal, {0.f, 1.f, 0.f}));
		float bouDif = lks::Saturate(lks::Dot(normal, {0.f, -1.f, 0.f}));

		col = {0.0f, 0.0f, 0.0f};
		col += sunDif * sunCol;
		col += skyDif * skyCol;
		col += bouDif * bouCol;

		col *= material;
	}

	col = lks::Pow(col, 0.4545f);

	fragColor = col;
}
