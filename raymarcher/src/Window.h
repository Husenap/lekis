#pragma once

#include <windows.h>

#include "Image.h"

class Window {
public:
	Window(HWND hwnd);
	~Window();

	void SetPosAndSize(int x, int y, int w, int h);

	void DrawImage(const Image& image);

private:
	void UpdateWindowSize();

	HWND mHwnd;
	HDC mDC;
	HDC mMemoryDC;
	int mWidth;
	int mHeight;
};
