#include <cassert>
#include <iostream>
#include <string>

#include "Raycaster.h"
#include "math/Vec2.h"
#include "math/Vec3.h"

void Raycaster::RenderScene() {
	auto& pixels = mFramebuffer.Pixels();
	int width    = mFramebuffer.GetWidth();
	int height   = mFramebuffer.GetHeight();

	int mapX = int(mPlayer.pos.x);
	int mapY = int(mPlayer.pos.y);

	for (int x = 0; x < width; ++x) {
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
		float dist = 0.f;

		if (horHit && vertHit) {
			dist = std::min(Length(mPlayer.pos - horIntersection), Length(mPlayer.pos - vertIntersection));
		} else if (horHit) {
			dist = Length(mPlayer.pos - horIntersection);
		} else if (vertHit) {
			dist = Length(mPlayer.pos - vertIntersection);
		}

		//std::cout << x << " - d: " << dist << ", a: " << rayAngle << std::endl;

		for (int y = 0; y < height; ++y) {
			int ceiling = (0.5f * height) - (height / dist);
			int floor   = height - ceiling;

			float c;

			if (y < ceiling) {
				c = 0.0f;
			} else if (y > ceiling && y <= floor) {
				c = 1.0f * (1.0f - dist / mMap.GetHeight());
			} else {
				c = 0.3f;
			}

			pixels[y * width + x] = ToColor(lks::vec3{1.0f, 1.0f, 1.0f} * c);
		}
	}
	//system("pause");
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

void Raycaster::RenderSceneOld() {
	auto& pixels = mFramebuffer.Pixels();
	int width    = mFramebuffer.GetWidth();
	int height   = mFramebuffer.GetHeight();

	for (int x = 0; x < width; ++x) {
		float rayAngle = (mPlayer.lookAngle + 0.5f * mPlayer.fov) - (x / float(width)) * mPlayer.fov;
		float rayLen   = 0.0f;

		lks::vec2 rayDir = lks::vec2::FromAngle(rayAngle);

		bool hitWall = false;
		while (!hitWall && rayLen < mMaxDepth) {
			rayLen += sampleInterval;

			lks::vec2 samplePos = mPlayer.pos + rayDir * rayLen;

			int sampleX = (int)samplePos.x;
			int sampleY = (int)samplePos.y;

			if (sampleX < 0 || sampleX >= mMap.GetWidth() || sampleY < 0 || sampleY >= mMap.GetHeight()) {
				hitWall = true;
				rayLen  = mMaxDepth;
			} else {
				if (mMap[sampleY * mMap.GetWidth() + sampleX] == '#') {
					hitWall = true;
				}
			}
		}

		rayLen *= std::cosf(rayAngle - mPlayer.lookAngle);

		for (int y = 0; y < height; ++y) {
			int ceiling = (0.5f * height) - (height / rayLen);
			int floor   = height - ceiling;

			float c;

			if (y < ceiling) {
				c = 0.0f;
			} else if (y > ceiling && y <= floor) {
				c = 1.0f * (1.0f - rayLen / mMaxDepth);
			} else {
				c = 0.3f;
			}

			pixels[y * width + x] = ToColor(lks::vec3{1.0f, 1.0f, 1.0f} * c);
		}
	}

	mFramebuffer.UpdateBitmap();
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
