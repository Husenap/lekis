#pragma once

#include <algorithm>
#include <cmath>

namespace lks {

class vec3 {
public:
	union {
		struct {
			float x, y, z;
		};
		struct {
			float r, g, b;
		};
	};

	vec3& operator+=(const float& v);
	vec3& operator-=(const float& v);
	vec3& operator+=(const vec3& v);
	vec3& operator-=(const vec3& v);
	vec3& operator*=(const vec3& v);
	vec3& operator*=(const float& v);
	vec3& operator/=(const vec3& v);
	vec3& operator/=(const float& v);

	static vec3 FromAngle(const float a, const float b = 0.0f);
};

static vec3 operator+(const vec3& a, const float& b) {
	return vec3{a.x + b, a.y + b, a.z + b};
}
static vec3 operator-(const vec3& a, const float& b) {
	return vec3{a.x - b, a.y - b, a.z - b};
}
static vec3 operator+(const vec3& a, const vec3& b) {
	return vec3{a.x + b.x, a.y + b.y, a.z + b.z};
}
static vec3 operator-(const vec3& a, const vec3& b) {
	return vec3{a.x - b.x, a.y - b.y, a.z - b.z};
}
static vec3 operator*(const vec3& a, const float& b) {
	return vec3{a.x * b, a.y * b, a.z * b};
}
static vec3 operator*(const float& b, const vec3& a) {
	return a * b;
}
static vec3 operator/(const vec3& a, const float& b) {
	return vec3{a.x / b, a.y / b, a.z / b};
}
static float Length(const vec3& v) {
	return std::sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}
static vec3 Normalize(const vec3& v) {
	return v / Length(v);
}
static float Dot(const vec3& a, const vec3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
static vec3 Pow(const vec3& v, const vec3& p) {
	return vec3{std::powf(v.x, p.x), std::powf(v.y, p.y), std::powf(v.z, p.z)};
}
static vec3 Pow(const vec3& v, float p) {
	return vec3{std::powf(v.x, p), std::powf(v.y, p), std::powf(v.z, p)};
}

static int32_t ToColor(const vec3& v) {
	return (int32_t(std::clamp(v.r, 0.0f, 1.0f) * 255.f) << 16) | (int32_t(std::clamp(v.g, 0.0f, 1.0f) * 255.f) << 8) |
	       (int32_t(std::clamp(v.b, 0.0f, 1.0f) * 255.f));
}
static int32_t ToColor(const float& v) {
	return ToColor(vec3{v, v, v});
}

}  // namespace lks
