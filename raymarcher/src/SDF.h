#pragma once

#include "Vec3.h"

static float sdSphere(const vec3& p, float radius) {
	return Length(p) - radius;
}

static float sdBox(const vec3& p, const vec3& b) {
	vec3 h{std::fabsf(p.x) - b.x, std::fabsf(p.y) - b.y, std::fabsf(p.z) - b.z};
	return std::fmaxf(std::fmaxf(h.x, h.y), h.z);
}
