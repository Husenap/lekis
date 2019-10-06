#pragma once

#include <algorithm>
#include <cmath>

namespace lks {

class vec2 {
public:
	float x, y;

	vec2& operator+=(const vec2& v);
	vec2& operator-=(const vec2& v);
	vec2& operator*=(const vec2& v);
	vec2& operator*=(const float& v);
	vec2& operator/=(const vec2& v);
	vec2& operator/=(const float& v);

	static vec2 FromAngle(const float a);
};


static vec2 operator+(const vec2& a, const vec2& b) {
	return vec2{a.x + b.x, a.y + b.y};
}
static vec2 operator-(const vec2& a, const vec2& b) {
	return vec2{a.x - b.x, a.y - b.y};
}
static vec2 operator*(const vec2& a, const float& b) {
	return vec2{a.x * b, a.y * b};
}
static vec2 operator*(const float& b, const vec2& a) {
	return a * b;
}
static vec2 operator/(const vec2& a, const float& b) {
	return vec2{a.x / b, a.y / b};
}
static float Length(const vec2& v) {
	return std::sqrtf(v.x * v.x + v.y * v.y);
}
static vec2 Normalize(const vec2& v) {
	return v / Length(v);
}
static float Dot(const vec2& a, const vec2& b) {
	return a.x * b.x + a.y * b.y;
}
static vec2 Pow(const vec2& v, const vec2& p) {
	return vec2{std::powf(v.x, p.x), std::powf(v.y, p.y)};
}
static vec2 Pow(const vec2& v, float p) {
	return vec2{std::powf(v.x, p), std::powf(v.y, p)};
}

}  // namespace lks
