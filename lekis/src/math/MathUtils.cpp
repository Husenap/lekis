#include <algorithm>

namespace lks {

float Smoothstep(float low, float high, float t) {
	t = std::clamp((t - low) / (high - low), 0.0f, 1.f);
	return t * t * (3.f - 2.f * t);
}

float Saturate(float f) {
	return std::clamp(f, 0.f, 1.f);
}

}  // namespace lks
