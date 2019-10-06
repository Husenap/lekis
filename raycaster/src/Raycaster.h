#pragma once

#define NOMINMAX
#include "Map.h"
#include "Player.h"
#include "rendering/Image.h"

class Raycaster {
public:
	Raycaster(lks::Image& framebuffer);

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

	const float mWallHeight = 1.5f;
	float mDistToProjectionPlane;
	float mHalfScreen;
};