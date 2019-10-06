#include "Vec2.h"

namespace lks {

vec2& vec2::operator+=(const vec2& v) {
	x += v.x;
	y += v.y;
	return *this;
}

vec2& vec2::operator-=(const vec2& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}

vec2& vec2::operator*=(const float& v) {
	x *= v;
	y *= v;
	return *this;
}

vec2& vec2::operator*=(const vec2& v) {
	x *= v.x;
	y *= v.y;
	return *this;
}

vec2& vec2::operator/=(const float& v) {
	x /= v;
	y /= v;
	return *this;
}

vec2& vec2::operator/=(const vec2& v) {
	x /= v.x;
	y /= v.y;
	return *this;
}

vec2 vec2::FromAngle(const float a) {
	return vec2{cosf(a), -sinf(a)};
}

}  // namespace lks
