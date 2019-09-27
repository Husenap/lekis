#include "Image.h"

Image::Image(int width, int height)
    : mWidth(width)
    , mHeight(height)
    , mBitmap(0) {
	mPixels.resize((size_t)mWidth * mHeight);
	std::fill(mPixels.begin(), mPixels.end(), 0);
}

Image::~Image() {
	DeleteObject(mBitmap);
}

void Image::CreateBitmap() {
	mBitmap = ::CreateBitmap(mWidth, mHeight, 1, 32, mPixels.data());
}
