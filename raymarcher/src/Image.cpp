#include "Image.h"

Image::Image(int width, int height)
    : mWidth(width)
    , mHeight(height)
    , mBitmap(0) {
	mPixels.resize((size_t)mWidth * mHeight, 0);
}

Image::~Image() {
	DeleteObject(mBitmap);
}

void Image::CreateBitmap() {
	mBitmap = ::CreateBitmap(mWidth, mHeight, 1, 32, mPixels.data());
}

void Image::UpdateBitmap() {
	SetBitmapBits(mBitmap, sizeof(mPixels[0]) * mPixels.size(), mPixels.data());
}
