#include <cassert>
#include <execution>
#include <iostream>
#include <string>

#include "Raycaster.h"
#include "math/Vec2.h"
#include "math/Vec3.h"

Raycaster::Raycaster(lks::Image& framebuffer)
    : mFramebuffer(framebuffer)
    , mPlayer{2.f, 13.f} {
	mDistToProjectionPlane = (0.5f * mFramebuffer.GetWidth()) / tanf(0.5f * mPlayer.fov);
	mHalfScreen            = 0.5f * mFramebuffer.GetHeight();
}

void Raycaster::RenderScene(float t) {
	auto& pixels = mFramebuffer.Pixels();
	int width    = mFramebuffer.GetWidth();
	int height   = mFramebuffer.GetHeight();

	int mapX = int(mPlayer.pos.x);
	int mapY = int(mPlayer.pos.y);

	std::for_each(std::execution::par, mFramebuffer.IndicesX().begin(), mFramebuffer.IndicesX().end(), [&](int x) {
		float rayAngle = (mPlayer.lookAngle + 0.5f * mPlayer.fov) - (x / float(width)) * mPlayer.fov;

		if (rayAngle < 0) {
			rayAngle += 2.f * lks::PI;
		} else if (rayAngle > 2.0 * lks::PI) {
			rayAngle -= 2.f * lks::PI;
		}

		bool rayFacingUp    = rayAngle > 0.f && rayAngle < lks::PI;
		bool rayFacingRight = rayAngle < 0.5f * lks::PI || rayAngle > 1.5f * lks::PI;
		bool horHit         = false;
		bool vertHit        = false;

		lks::vec2 horIntersection = {0.f, 0.f};
		if (rayAngle != 0.f && rayAngle != lks::PI) {
			// find horizontal intersection

			if (rayFacingUp) {
				horIntersection.y = float(mapY);
			} else {
				horIntersection.y = float(mapY + 1);
			}

			horIntersection.x = mPlayer.pos.x + (mPlayer.pos.y - horIntersection.y) / std::tanf(rayAngle);

			horHit = IsWall(lks::vec2{horIntersection.x, horIntersection.y - (rayFacingUp ? 1.f : 0.f)});

			if (!horHit) {
				lks::vec2 step;

				if (rayFacingUp) {
					step.y = -1.f;
					step.x = 1.f / tanf(rayAngle);
				} else {
					step.y = 1.f;
					step.x = -1.f / tanf(rayAngle);
				}

				while (!horHit && horIntersection.x <= mMap.GetHeight() - 1.f && horIntersection.x >= 0.f) {
					horIntersection += step;
					horHit = IsWall(lks::vec2{horIntersection.x, horIntersection.y - (rayFacingUp ? 1.f : 0.f)});
				}
			}
		}

		lks::vec2 vertIntersection = {0.f, 0.f};
		if (rayAngle != 0.5f * lks::PI && rayAngle != 1.5f * lks::PI) {
			// find vertical intersection

			if (rayFacingRight) {
				vertIntersection.x = float(mapX + 1);
			} else {
				vertIntersection.x = float(mapX);
			}

			vertIntersection.y = mPlayer.pos.y + (mPlayer.pos.x - vertIntersection.x) * std::tanf(rayAngle);

			vertHit = IsWall(lks::vec2{vertIntersection.x - (rayFacingRight ? 0.f : 1.f), vertIntersection.y});

			if (!vertHit) {
				lks::vec2 step;

				if (rayFacingRight) {
					step.x = 1.f;
					step.y = -tanf(rayAngle);
				} else {
					step.x = -1.f;
					step.y = tanf(rayAngle);
				}

				while (!vertHit && vertIntersection.y <= mMap.GetWidth() - 1.f && vertIntersection.y >= 0.f) {
					vertIntersection += step;
					vertHit = IsWall(lks::vec2{vertIntersection.x - (rayFacingRight ? 0.f : 1.f), vertIntersection.y});
				}
			}
		}

		// calculate closest distance
		lks::vec2 fragCoord{0.f, 0.f};
		float dist = 0.f;

		float verticalDistance   = Length(mPlayer.pos - vertIntersection);
		float horizontalDistance = Length(mPlayer.pos - horIntersection);
		dist                     = std::min(verticalDistance, horizontalDistance);

		dist *= std::cosf(rayAngle - mPlayer.lookAngle) * 0.75f + 0.25f;  // fisheye correction

		if (verticalDistance < horizontalDistance) {
			fragCoord.x = std::fmodf(vertIntersection.y, 1.0f);
			if (!rayFacingRight) {
				fragCoord.x = 1.f - fragCoord.x;
			}
		} else {
			fragCoord.x = std::fmodf(horIntersection.x, 1.0f);
			if (!rayFacingUp) {
				fragCoord.x = 1.f - fragCoord.x;
			}
		}

		float projectedHeight = (mWallHeight / dist) * mDistToProjectionPlane;
		float ceiling = mHalfScreen - 0.5f * projectedHeight;
		float floor   = mHalfScreen + 0.5f * projectedHeight;

		for (int y = 0; y < height; ++y) {
			lks::vec3 c{0.0f, 0.0f, 0.0f};

			if (y < ceiling) {  // ceiling
				c += 0.1f;
			} else if (y < mHalfScreen + 0.5f * projectedHeight) {  // wall
				fragCoord.y = ((float)y - (float)ceiling) / ((float)floor - (float)ceiling);

				lks::vec2 uv = fragCoord;

				uv = uv * 2.f - 1.f;
				uv -= lks::vec2{std::cosf(t), std::sinf(t)} * 0.5f;
				c += lks::Smoothstep(0.049f, 0.05f, std::fabsf(Length(uv) - 0.4f));
			} else {  // floor
				c += 0.3f;
			}

			pixels[y * width + x] = ToColor(c);
		}
	});
	mFramebuffer.UpdateBitmap();
}

bool Raycaster::IsWall(const lks::vec2& pos) const {
	int mapX = int(pos.x);
	int mapY = int(pos.y);

	if (mapY > mMap.GetHeight() - 1 || mapY < 0 || mapX > mMap.GetWidth() - 1 || mapX < 0) {
		return false;
	}

	return mMap[mapY * mMap.GetWidth() + mapX] == '#';
}

void Raycaster::UpdateScene(float dt) {
	bool modifier = GetAsyncKeyState(VK_CONTROL);

	if (GetAsyncKeyState(VK_LEFT)) {
		if (modifier) {
			mPlayer.pos += lks::vec2::FromAngle(mPlayer.lookAngle - 0.5f * lks::PI) * mPlayer.speed * dt;
		} else {
			mPlayer.lookAngle += mPlayer.lookSens * dt;
			if (mPlayer.lookAngle > 2.f * lks::PI) {
				mPlayer.lookAngle -= 2.f * lks::PI;
			}
		}
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		if (modifier) {
			mPlayer.pos += lks::vec2::FromAngle(mPlayer.lookAngle + 0.5f * lks::PI) * mPlayer.speed * dt;
		} else {
			mPlayer.lookAngle -= mPlayer.lookSens * dt;
			if (mPlayer.lookAngle < 0) {
				mPlayer.lookAngle += 2.f * lks::PI;
			}
		}
	}

	if (GetAsyncKeyState(VK_UP)) {
		mPlayer.pos += lks::vec2::FromAngle(mPlayer.lookAngle) * mPlayer.speed * dt;
	}

	if (GetAsyncKeyState(VK_DOWN)) {
		mPlayer.pos -= lks::vec2::FromAngle(mPlayer.lookAngle) * mPlayer.speed * dt;
	}
}

const std::string Raycaster::GetMapString() const {
	return mMap.ToString(mPlayer);
}

const Player& Raycaster::GetPlayer() const {
	return mPlayer;
}
