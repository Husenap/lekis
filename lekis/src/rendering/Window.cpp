#include "Window.h"

#include <cmath>

namespace lks {

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
	SetWindowPos(mHwnd, NULL, x, y, w + (w - mWidth), h + (h - mHeight), 0);
	UpdateWindowSize();
}

void Window::SetFont(int font) {
	HFONT hfont = (HFONT)GetStockObject(font);
	SelectObject(mMemoryDC, hfont);
}

void Window::RenderText(const std::string& text, int x, int y, int color) {
	SetTextColor(mMemoryDC, color);
	SetBkColor(mMemoryDC, TRANSPARENT);
	RECT rect{x, y, 0, 0};
	DrawText(mMemoryDC, text.c_str(), -1, &rect, DT_NOCLIP);
}

void Window::SetRenderTarget(const Image& image) {
	SelectObject(mMemoryDC, image.GetBitmap());
	mTargetWidth  = image.GetWidth();
	mTargetHeight = image.GetHeight();
}

void Window::Present() {
	UpdateWindowSize();

	float windowRatio = (float)mWidth / (float)mHeight;
	float imageRatio  = (float)mTargetWidth / (float)mTargetHeight;

	float width  = mTargetWidth;
	float height = mTargetHeight;

	if (windowRatio > imageRatio) {
		width *= (float)mHeight / (float)mTargetHeight;
		height = (float)mHeight;
	} else {
		height *= (float)mWidth / (float)mTargetWidth;
		width = (float)mWidth;
	}

	StretchBlt(mDC,
	           (mWidth - width) * 0.5f,
	           (mHeight - height) * 0.5f,
	           width,
	           height,
	           mMemoryDC,
	           0,
	           0,
	           mTargetWidth,
	           mTargetHeight,
	           SRCCOPY);
}

void Window::UpdateWindowSize() {
	RECT rect;
	GetClientRect(mHwnd, &rect);
	mWidth  = rect.right - rect.left;
	mHeight = rect.bottom - rect.top;
}

}  // namespace lks
