#pragma once

#include <windows.h>

#include "Image.h"

class Window {
public:
	Window(HWND hwnd);
	~Window();

	void SetPosAndSize(int x, int y, int w, int h);

	void DrawImage(const Image& image, int x, int y, int scale);

private:
	HWND mHwnd;
	HDC mDC;
	HDC mMemoryDC;
	RECT mRect;

	void UpdatePos();
	LONG Width() const { return mRect.right - mRect.left; }
	LONG Height() const { return mRect.bottom - mRect.top; }
};
