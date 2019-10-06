#include <string>

#include "Map.h"
#include "Player.h"

std::string Map::ToString(const Player& player) const {

	std::string mapWPlayer;

	for (int mapIdx = 0; mapIdx < mWidth * mHeight; ++mapIdx) {
		int x = mapIdx % mWidth;
		int y = mapIdx / mWidth;

		if (x == (int)player.pos.x && y == (int)player.pos.y) {
			mapWPlayer += 'P';
		}
		else {
			mapWPlayer += mMap[mapIdx];
		}

		if (x == (mWidth - 1)) {
			mapWPlayer += '\n';
		}
	}

	return mapWPlayer;
}

void Map::Init() {
	mMap += "################";
	mMap += "#..............#";
	mMap += "#..............#";
	mMap += "#..............#";
	mMap += "#..............#";
	mMap += "#..............#";
	mMap += "#..............#";
	mMap += "#..............#";
	mMap += "#..............#";
	mMap += "#..............#";
	mMap += "#..............#";
	mMap += "#..............#";
	mMap += "#..............#";
	mMap += "#..............#";
	mMap += "#..............#";
	mMap += "################";

	mWidth = 16;
	mHeight = 16;
}
