#include "game.h"
#include "sgg/graphics.h"
#include "defines.h"
#include "laser.h"

void Game::spawnenemy()
{
	if (!enemy)
	{
		enemy = new Enemy(*this);
	}
}

void Game::spawnlaser()
{
	if (!laser)
	{
		laser  = new Laser(*this);
	}
}

void Game::checklaser()
{
	if (laser && !laser->isActive())
	{
		delete laser;
		laser = nullptr;
	}
}

void Game::checkenemy()
{
	if (enemy && !enemy->isActive())
	{
		delete enemy;
		enemy = nullptr;
	}
}

bool Game::checkLaserCollision()
{
	if (!laser || !enemy)
	{
		return false;
	}

	Disk d1 = laser->getCollisionHull();
	Disk d2 = enemy->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius && laser->visible)
	{
		enemy->drainLife(0.1f);
		return true;
	}
	else
		return false;
}

bool Game::checkCollision()
{
	if (!player || !enemy )
	{
		return false;
	}

	Disk d1 = player->getCollisionHull();
	Disk d2 = enemy->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
	{
		player->drainLife(0.1f);
		return true;
	}
	else
		return false;
}

void Game::updateStartScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		status = STATUS_PLAYING;
		startTime = graphics::getGlobalTime();
	}

	graphics::MouseState ms;
	graphics::getMouseState(ms);
	if (ms.button_left_pressed)
	{
		status = STATUS_PLAYING;	
		startTime = graphics::getGlobalTime();
	}
}

void Game::updateLevelScreen()
{
	if (!player_initialized && graphics::getGlobalTime() > 1000)
	{
		player = new Player(*this);
		player_initialized = true;
	}

	if (player)
		player->update();

	checkenemy();
	spawnenemy();
	spawnlaser();

	if (enemy)
		enemy->update();

	if (laser)
	{
		laser->update();
	}
		
		
	
	if (checkLaserCollision())
	{
		delete laser;
		laser = nullptr;
		if (enemy->getRemainingLife() == 0.0f)
			enemies_killed += 1;
	}

	if (checkCollision())
	{
		player->drawCollision(0.3);
		delete enemy;
		enemy = nullptr;
		graphics::playSound(ASSET_PATH + std::string("hurt.mp3"), 0.6f);
	}

	if (player && player->getRemainingLife() == 0.0f)
	{
		status = STATUS_END;
		endTime = graphics::getGlobalTime();
	}
}

void Game::updateEndScreen()
{
	elapsedTime = endTime - startTime;
}

void Game::drawStartScreen()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string("background.png");

	//draw background
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	char info[40];
	sprintf_s(info, "Press ENTER to start");
	graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 3, 40, info, br);

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	graphics::drawDisk(window2canvasX(ms.cur_pos_x), window2canvasY(ms.cur_pos_y), 10, br);
}

void Game::drawLevelScreen()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string("background.png");

	//draw background
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	//draw player
	if (player)
		player->draw();
	//draw enemy
	if (enemy)
		enemy->draw();
	//draw laser
	if (laser && graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		laser->laser_pos_x = player->getPosX() + 60.0f;
		laser->laser_pos_y = player->getPosY();
	}
	if ( laser)
		laser->draw();
	

	float player_life = player ? player->getRemainingLife() : 0.0f;


	//draw player life bar
	br.fill_color[0] = 0.2f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 0.2f;
	br.texture = "";
	br.fill_secondary_color[0] = 0.2f * (1.0f - player_life) + player_life * 0.2f;
	br.fill_secondary_color[1] = 0.2f;
	br.fill_secondary_color[2] = 1.0f * (1.0f - player_life) + player_life * 1.0f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;
	graphics::drawRect(CANVAS_WIDTH - 100 - ((1.0f - player_life) * 120 / 2), 30, player_life * 120, 20, br);

	br.outline_opacity = 1.0f;
	br.gradient = false;
	br.fill_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH - 100, 30, 120, 20, br);


	float enemy_life = enemy ? enemy->getRemainingLife() : 0.0f;
	enemy->setEnemyLife(enemy_life);
}

void Game::drawEndScreen()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string("background.png");

	//draw background
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	char info[40];
	sprintf_s(info, "END GAME");
	graphics::drawText(CANVAS_WIDTH / 2 - 75.0f, CANVAS_HEIGHT / 3, 40, info, br);

	char timeInfo[50];
	sprintf_s(timeInfo, "Time: %.2f seconds", elapsedTime/1000.0f);
	graphics::drawText(CANVAS_WIDTH / 2 - 70.0f, CANVAS_HEIGHT / 2, 20, timeInfo, br);

	char intinfo[40];
	sprintf_s(intinfo, "Enemies Killed: %.2i", enemies_killed);
	graphics::drawText(CANVAS_WIDTH / 2 - 70.0f, CANVAS_HEIGHT / 2 +50.0f, 20, intinfo, br);

}

void Game::update()
{
	if (status == STATUS_START)
	{
		updateStartScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		updateLevelScreen();
	}
	else 
	{
		updateEndScreen();
	}
}

void Game::draw()
{

	if (status == STATUS_START)
	{
		drawStartScreen();
	}
	else  if (status == STATUS_PLAYING)
	{
		drawLevelScreen();
	}
	else
	{
		drawEndScreen();
	}
}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "bitstream.otf");
	graphics::playMusic(std::string(ASSET_PATH) + "alive.mp3", 0.1f, 1, 4000);
}

float Game::window2canvasX(float x)
{
	return x * CANVAS_WIDTH / (float)window_width;
}

float Game::window2canvasY(float y)
{
	return y * CANVAS_HEIGHT / (float)window_height;
}


Game::Game()
{
}

Game::~Game()
{
	if (player)
	{
		delete  player;
	}
}
