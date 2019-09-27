#pragma once

#include "Image.h"
#include "Vec3.h"

class Raymarcher {
public:
	Raymarcher();
	~Raymarcher();

	void RenderOnTarget(Image& framebuffer);

private:
	float Map(vec3 p);
	float RayMarch(vec3 ro, vec3 rd);
	vec3 CalcNormal(vec3 p);

};