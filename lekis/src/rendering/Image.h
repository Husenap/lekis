#pragma once

#include <windows.h>
#include <vector>

namespace lks {

class Image {
public:
	Image(int width, int height);
	~Image();

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

	void CreateBitmap();

	std::vector<int32_t>& Pixels() { return mPixels; }
	const std::vector<int32_t>& Pixels() const { return mPixels; }
	const std::vector<int32_t>& Indices() const { return mIndices; }
	const std::vector<int32_t>& IndicesX() const { return mIndicesX; }
	const std::vector<int32_t>& IndicesY() const { return mIndicesY; }
	const HBITMAP& GetBitmap() const { return mBitmap; }

	void UpdateBitmap();

private:
	int mWidth;
	int mHeight;
	std::vector<int32_t> mPixels;
	std::vector<int32_t> mIndices;
	std::vector<int32_t> mIndicesX;
	std::vector<int32_t> mIndicesY;
	HBITMAP mBitmap;
};

}  // namespace lks
