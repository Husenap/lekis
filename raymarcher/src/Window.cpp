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

void Window::DrawImage(const Image& image, int x, int y) {
	SelectObject(mMemoryDC, image.GetBitmap());
	BitBlt(mDC, x, y, image.GetWidth(), image.GetHeight(), mMemoryDC, 0, 0, SRCCOPY);
}
