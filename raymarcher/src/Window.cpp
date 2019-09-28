#include "Window.h"

#include <string>

Window::Window(HWND hwnd)
    : mHwnd(hwnd)
    , mDC(GetDC(hwnd))
    , mMemoryDC(CreateCompatibleDC(mDC))
    , mWidth(0)
    , mHeight(0) {}

Window::~Window() {
	DeleteDC(mMemoryDC);
	ReleaseDC(mHwnd, mDC);
}

void Window::SetPosAndSize(int x, int y, int w, int h) {
	SetWindowPos(mHwnd, NULL, x, y, w, h, 0);
	UpdateWindowSize();
}

void Window::DrawImage(const Image& image) {
	UpdateWindowSize();

	float windowRatio = (float)mWidth / (float)mHeight;
	float imageRatio  = (float)image.GetWidth() / (float)image.GetHeight();

	float width  = image.GetWidth();
	float height = image.GetHeight();

	if (windowRatio > imageRatio) {
		width *= (float)mHeight / (float)image.GetHeight();
		height = (float)mHeight;
	} else {
		height *= (float)mWidth / (float)image.GetWidth();
		width = (float)mWidth;
	}

	SelectObject(mMemoryDC, image.GetBitmap());
	StretchBlt(mDC,
	           (mWidth - width) * 0.5f,
	           (mHeight - height) * 0.5f,
	           width,
	           height,
	           mMemoryDC,
	           0,
	           0,
	           image.GetWidth(),
	           image.GetHeight(),
	           SRCCOPY);


}

void Window::UpdateWindowSize() {
	RECT rect;
	GetClientRect(mHwnd, &rect);
	mWidth  = rect.right - rect.left;
	mHeight = rect.bottom - rect.top;
}
