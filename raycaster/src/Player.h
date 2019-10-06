#pragma once

#include "math/Vec2.h"
#include "math/MathUtils.h"

struct Player {
	lks::vec2 pos   = {0.0f, 0.0f};
	float lookAngle = 2.1f;
	float fov       = 60.f * (lks::PI / 180.f);
	float speed     = 5.0f;
	float lookSens  = 3.5f;
};