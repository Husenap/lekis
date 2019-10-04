#pragma once

#include "math/Vec3.h"
#include "math/MathUtils.h"

struct Player {
	lks::vec3 pos   = {0.0f, 0.0f, 0.0f};
	float lookAngle = 0.0f;
	float fov       = 103.f * (lks::PI / 180.f);
	float speed     = 5.0f;
};