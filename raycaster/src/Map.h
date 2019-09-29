#pragma once

#include "Player.h"

class Map {
public:
	Map() { Init(); }

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

	char operator[](int i) const { return mMap[i]; }

	std::string ToString(Player& player) const;

private:
	int mWidth;
	int mHeight;
	std::string mMap;

	void Init();
};