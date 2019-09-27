#include "Raymarcher.h"

#include "SDF.h"

const int MAX_STEPS  = 256;
const float MIN_DIST = 0.01f;
const float MAX_DIST = 20.f;

Raymarcher::Raymarcher() {}

Raymarcher::~Raymarcher() {}

void Raymarcher::RenderOnTarget(Image& framebuffer) {
	auto& pixels = framebuffer.Pixels();
	int width    = framebuffer.GetWidth();
	int height   = framebuffer.GetHeight();
	for (int i = 0; i < pixels.size(); ++i) {
		int x = i % width;
		int y = i / width;

		vec3 uv = {0.0f};
		uv.x    = ((float)x / (float)width) * 2.f - 1.f;
		uv.y    = (1.f - ((float)y / (float)height)) * 2.f - 1.f;
		uv.x *= float(width) / float(height);

		vec3 ro = vec3{0.f, 0.f, -3.f};
		vec3 rd = Normalize(vec3{uv.x, uv.y, 0.8f});

		float t = RayMarch(ro, rd);

		vec3 col = vec3{0.0f, 0.0f, 0.0f};

		if (t < MAX_DIST) {
			vec3 position = ro + rd * t;
			vec3 normal   = CalcNormal(position);

			vec3 material = vec3{0.2f, 0.2f, 0.2f};

			vec3 sunCol = vec3{7.f, 4.5f, 3.5f};
			vec3 skyCol = vec3{0.533f, 0.808f, 0.9f};
			vec3 bouCol = vec3{0.7, 0.3, 0.2f};

			vec3 sunDir = vec3{0.65f, 0.35f, 0.2f};

			float sunDif = Saturate(Dot(normal, sunDir));
			float skyDif = 0.5f + 0.5f * Saturate(Dot(normal, vec3{0.f, 1.f, 0.f}));
			float bouDif = Saturate(Dot(normal, vec3{0.f, -1.f, 0.f}));

			col = vec3{0.0f, 0.0f, 0.0f};
			col += sunDif * sunCol;
			col += skyDif * skyCol;
			col += bouDif * bouCol;

			col *= material;
		}

		col = Pow(col, 0.4545f);

		pixels[i] = ToColor(col);
	}
}

float Raymarcher::Map(vec3 p) {
	float radius = 1.f;
	float sphere = sdSphere(p - vec3{std::sinf(mTime), 0.f, 0.f}, radius);
	float box    = sdBox(p - vec3{4.f, 0.f, 1.f}, {1.f, 1.f, 2.f});
	float plane  = p.y + radius;

	float d = std::fminf(sphere, plane);
	d       = std::fminf(d, box);

	return d;
}

float Raymarcher::RayMarch(vec3 ro, vec3 rd) {
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

vec3 Raymarcher::CalcNormal(vec3 p) {
	const vec3 e = vec3{1.0, -1.0, 0.0} * 0.0002f;
	const vec3 xyy{e.x, e.y, e.y};
	const vec3 yyx{e.y, e.y, e.x};
	const vec3 yxy{e.y, e.x, e.y};
	const vec3 xxx{e.x, e.x, e.x};
	return Normalize(xyy * Map(p + xyy) + yyx * Map(p + yyx) + yxy * Map(p + yxy) + xxx * Map(p + xxx));
}
