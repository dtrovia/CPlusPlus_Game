#include "player.h"
#include "gameobject.h"
#include "sgg/graphics.h"
#include "game.h"
#include "laser.h"
#include <chrono>
#include <thread> 

Player::Player(const Game& mygame)
	:GameObject(mygame)
{

}

void Player::update()
{
	const int gravity = 5;

	if (graphics::getKeyState(graphics::SCANCODE_LEFT))
	{
		pos_x -= speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_RIGHT))
	{
		pos_x += speed * graphics::getDeltaTime() / 10.0f;
	}

	if (graphics::getKeyState(graphics::SCANCODE_UP))
	{
		if (isBottom && !isJumping)
		{
			graphics::playSound(ASSET_PATH + std::string("jump.mp3"), 0.6f);
			isJumping = true;
			isBottom = false;
		}
	}

	if (isJumping)
	{
		pos_y -= gravity ;
	}
	else
	{
		pos_y += gravity / 2.0f;
	}

	if (pos_y >= ((2 * CANVAS_HEIGHT) / 3)+10)
	{
		pos_y = ((2 * CANVAS_HEIGHT) / 3)+10;
		isBottom = true;
	}
	if (pos_y <= ((2 * CANVAS_HEIGHT) / 3) - 200)
	{
		isJumping = false;  
	}

	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH;
}


void Player::draw()
{
	graphics::Brush br;
	br.fill_opacity = 1.0f;
	br.outline_opacity = 0.0f;

	if (drawInRed)
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		auto elapsedSeconds = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - colorChangeStartTime).count();

		if (elapsedSeconds < redDurationInSeconds)
		{
			br.texture = std::string(ASSET_PATH) + std::string("playerRed.png");
		}
		else
		{
			drawInRed = false;
			br.texture = std::string(ASSET_PATH) + std::string("player.png");
		}
	}
	else
	{
		br.texture = std::string(ASSET_PATH) + std::string("player.png");
	}

	graphics::drawRect(pos_x, pos_y, 100, 100, br);
}


void Player::drawCollision(double durationInSeconds)
{
	drawInRed = true;
	colorChangeStartTime = std::chrono::high_resolution_clock::now();
	redDurationInSeconds = durationInSeconds;
}

void Player::init()
{
}



Disk Player::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 55.0f;
	return disk;
}


