#include "Vec3.h"

namespace lks {

vec3& vec3::operator+=(const vec3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

vec3& vec3::operator-=(const vec3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

vec3& vec3::operator*=(const float& v) {
	x *= v;
	y *= v;
	z *= v;
	return *this;
}

vec3& vec3::operator*=(const vec3& v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

vec3& vec3::operator/=(const float& v) {
	x /= v;
	y /= v;
	z /= v;
	return *this;
}

vec3& vec3::operator/=(const vec3& v) {
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

vec3 vec3::FromAngle(const float a, const float b) {
	return vec3{cosf(a) * cosf(b), sinf(a) * cosf(b), sinf(b)};
}

}  // namespace lks
