#pragma once

#include <string>
#include <vector>

#pragma pack(push, 1)
struct PixelData {
	unsigned char b, g, r;
};
#pragma pack(pop)

class Bitmap {
public:
	Bitmap(const std::string& filePath);
	const std::vector<int32_t>& GetPixels() const { return mPixels; }

private:
	std::vector<int32_t> mPixels;
};