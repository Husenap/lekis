#include "Window.h"

Window::Window(HWND hwnd)
    : mHwnd(hwnd)
    , mDC(GetDC(hwnd))
    , mMemoryDC(CreateCompatibleDC(mDC)) {}

Window::~Window() {
	DeleteDC(mMemoryDC);
	ReleaseDC(mHwnd, mDC);
}

void Window::SetPosAndSize(int x, int y, int w, int h) {
	SetWindowPos(mHwnd, NULL, x, y, w, h, 0);
}

void Window::DrawImage(const Image& image, int x, int y, int scale) {
	SelectObject(mMemoryDC, image.GetBitmap());
	StretchBlt(mDC,
	           0,
	           0,
	           image.GetWidth() * scale,
	           image.GetHeight() * scale,
	           mMemoryDC,
	           0,
	           0,
	           image.GetWidth(),
	           image.GetHeight(),
	           SRCCOPY);
}
