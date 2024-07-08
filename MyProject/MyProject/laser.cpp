#include "laser.h"
#include "sgg/graphics.h"
#include "player.h"
#include "game.h"

Laser::Laser(const Game& mygame)
    :GameObject(mygame)
{
	init();
}


void Laser::update()
{
	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		graphics::playSound(ASSET_PATH + std::string("laser.mp3"), 0.03f);
	}
	laser_pos_x += speed * graphics::getDeltaTime() / 0.1f;

}

void Laser::draw()
{
	visible = true;
	graphics::Brush br;
	br.fill_opacity = 1.0f;
	br.outline_opacity = 0.0f;
	br.texture = std::string(ASSET_PATH) + std::string("laser.png");
	graphics::drawRect(laser_pos_x, laser_pos_y, 50, 50, br);
}

void Laser::init()
{
	size = 100 + 100 * rand0to1();
	speed = 0.3f;
	
}

Laser::~Laser()
{
}

Disk Laser::getCollisionHull() const
{
	Disk disk;
	disk.cx = laser_pos_x;
	disk.cy = laser_pos_y;
	disk.radius = 55.0f;
	return disk;
}




