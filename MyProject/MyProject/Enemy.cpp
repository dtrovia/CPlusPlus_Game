#include "Enemy.h"
#include "sgg/graphics.h"
#include "defines.h"
#include <random>
#include "game.h"

void Enemy::update()
{
	if (!enemy_initialized && graphics::getGlobalTime() > 1000)
	{
		enemy = new Enemy(*this);
		enemy_initialized = true;
	}

	pos_x -= speed * graphics::getDeltaTime();


	if (pos_x < -size || life ==0)
	{
		active = false;
	}

	if (pos_y < (2 * CANVAS_HEIGHT) / 3) pos_y = (2 * CANVAS_HEIGHT) / 3;
	if (pos_y > CANVAS_HEIGHT) pos_y = CANVAS_HEIGHT;
}

void Enemy::draw()
{

	graphics::Brush  brush;
	brush.fill_opacity = 1.0f;
	brush.outline_opacity = 0.0f;
	brush.texture = std::string(ASSET_PATH) + "enemy.png";
	graphics::drawRect(pos_x, pos_y-0.1*size, size, size, brush);

	//draw life bar
	brush.fill_color[0] = 1.0f;
	brush.fill_color[1] = 0.2f;
	brush.fill_color[2] = 0.2f;
	brush.texture = "";
	brush.fill_secondary_color[0] = 0.2f * (1.0f - life) + life * 0.2f;
	brush.fill_secondary_color[1] = 0.2f;
	brush.fill_secondary_color[2] = 1.0f * (1.0f - life) + life * 1.0f;
	brush.gradient = true;
	brush.gradient_dir_u = 1.0f;
	brush.gradient_dir_v = 0.0f;
	graphics::drawRect(pos_x - ((1.0f - life) * 120 / 2), pos_y-0.7*size, life * 120, 20, brush);

}

void Enemy::init()
{
	size = 100 + 100 * rand0to1();
	speed = 0.5f;
	pos_x = CANVAS_WIDTH;
	pos_y = CANVAS_HEIGHT /3;

	brush.outline_opacity = 0.0f;
}

Enemy::Enemy(const class Game& mygame)
	:GameObject(mygame)
{
	init();

}

Enemy::~Enemy()
{
}

Disk Enemy::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size * 0.45f;
	return disk;
}

