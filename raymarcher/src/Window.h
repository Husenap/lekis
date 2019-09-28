#pragma once

#include <windows.h>
#include <string>

#include "Image.h"

class Window {
public:
	Window(HWND hwnd);
	~Window();

	void SetPosAndSize(int x, int y, int w, int h);

	void RenderText(const std::string& text, int x, int y, int color);
	void SetRenderTarget(const Image& image);
	void Present();

private:
	void UpdateWindowSize();

	HWND mHwnd;
	HDC mDC;
	HDC mMemoryDC;
	int mWidth;
	int mHeight;
	int mTargetWidth;
	int mTargetHeight;
};
