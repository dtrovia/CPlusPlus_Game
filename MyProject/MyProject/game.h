#pragma once

#include "player.h"
#include "Enemy.h"
#include "laser.h"
#include <chrono>

class Game
{
	typedef enum { STATUS_START, STATUS_PLAYING, STATUS_END } status_t;
	Player* player = nullptr;
	bool player_initialized = false;
	bool debug_mode = false;
	Enemy* enemy = nullptr;
	Laser* laser = nullptr;
	void spawnenemy();
	void checkenemy();
	void spawnlaser();
	void checklaser();
	bool checkCollision();
	bool checkLaserCollision();
	status_t status = STATUS_START;
	float startTime;
	float elapsedTime;
	float endTime;

	unsigned int window_width = WINDOW_WIDTH,
		window_height = WINDOW_HEIGHT;

	void updateStartScreen();
	void updateLevelScreen();
	void updateEndScreen();
	void drawStartScreen();
	void drawLevelScreen();
	void drawEndScreen();

public:
	int enemies_killed = 0;
	void update();
	void draw();
	void init();
	unsigned int getWindowWidth() { return window_width; }
	unsigned int getWindowHieght() { return window_height; }
	float window2canvasX(float x);
	float window2canvasY(float y);
	void setWindowDimensions(unsigned int w, unsigned int h) { window_width = w, window_height = h; }
	Game();
	~Game();
};