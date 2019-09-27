#pragma once

#include <windows.h>
#include <vector>

class Image {
public:
	Image(int width, int height);
	~Image();

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

	void CreateBitmap();

	std::vector<int32_t>& Pixels() { return mPixels; }
	const std::vector<int32_t>& Pixels() const { return mPixels; }
	const HBITMAP& GetBitmap() const { return mBitmap; }

	void UpdateBitmap();

private:
	int mWidth;
	int mHeight;
	std::vector<int32_t> mPixels;
	HBITMAP mBitmap;
};