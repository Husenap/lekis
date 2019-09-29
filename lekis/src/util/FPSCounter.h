#pragma once

#include <vector>

namespace lks {

class FPSCounter {
public:
	FPSCounter(int stackSize);

	void PushTime(float time);
	float GetFPS();

private:
	int mMaxSize;
	int mCurrentIndex;
	std::vector<float> mStack;
};

}  // namespace lks
