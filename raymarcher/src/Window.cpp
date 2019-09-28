#include "Window.h"

#include <string>

Window::Window(HWND hwnd)
    : mHwnd(hwnd)
    , mDC(GetDC(hwnd))
    , mMemoryDC(CreateCompatibleDC(mDC))
    , mRect({NULL}) {}

Window::~Window() {
	DeleteDC(mMemoryDC);
	ReleaseDC(mHwnd, mDC);
}

void Window::SetPosAndSize(int x, int y, int w, int h) {
	SetWindowPos(mHwnd, NULL, x, y, w, h, 0);
}

void Window::DrawImage(const Image& image, int x, int y, int scale) {
	SelectObject(mMemoryDC, image.GetBitmap());
	UpdatePos();
	StretchBlt(mDC,
	           .5f * Width() - .5f * image.GetWidth() * scale,
	           .5f * Height() - .5f * image.GetHeight() * scale,
	           image.GetWidth() * scale,
	           image.GetHeight() * scale,
	           mMemoryDC,
	           0,
	           0,
	           image.GetWidth(),
	           image.GetHeight(),
	           SRCCOPY);


}

void Window::UpdatePos() {
	GetWindowRect(mHwnd, &mRect);
}
