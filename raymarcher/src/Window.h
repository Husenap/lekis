#pragma once

#include <windows.h>

#include "Image.h"

class Window {
public:
	Window(HWND hwnd);
	~Window();

	void SetPosAndSize(int x, int y, int w, int h);

	void DrawImage(const Image& image, int x, int y);

private:
	HWND mHwnd;
	HDC mDC;
	HDC mMemoryDC;
};
