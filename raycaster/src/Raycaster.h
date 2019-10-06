#pragma once

#define NOMINMAX
#include "Map.h"
#include "Player.h"
#include "rendering/Image.h"

class Raycaster {
public:
	Raycaster(lks::Image& framebuffer)
	    : mFramebuffer(framebuffer)
	    , mPlayer{2.f, 13.f}
	    , mMaxDepth(mMap.GetHeight()) {}

	void RenderScene(float t);
	bool IsWall(const lks::vec2& pos) const;
	void RenderSceneOld();
	void UpdateScene(float dt);
	const std::string GetMapString() const;
	const Player& GetPlayer() const;

private:
	lks::Image& mFramebuffer;
	Player mPlayer;
	Map mMap;

	const float sampleInterval = 0.0125f;
	const float mMaxDepth;
	const int gridSize = 64;
};