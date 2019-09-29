#pragma once

#include "rendering/Image.h"
#include "math/Vec3.h"

class Raymarcher {
public:
	Raymarcher();
	~Raymarcher();

	void RenderOnTarget(lks::Image& framebuffer);
	void SetTime(float t) { mTime = t; }

private:
	float Map(lks::vec3 p);
	lks::vec3 CalcNormal(lks::vec3 p);
	float RayMarch(lks::vec3 ro, lks::vec3 rd);
	void MainImage(lks::vec3& fragColor, const lks::vec3& fragCoord, const lks::vec3& resolution);

	float mTime = 0.f;
};
