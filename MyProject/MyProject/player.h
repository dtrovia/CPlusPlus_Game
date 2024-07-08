#pragma once
#include "defines.h"
#include "gameobject.h"
#include "laser.h"
#include <chrono>
#include <ctime>

class Player : public GameObject, public Collidable {

	float speed = 10.0f;
	float pos_x = CANVAS_WIDTH / 3, pos_y = CANVAS_HEIGHT / 3;
	float height = 1.0f;
	float life = 1.0f;

private:
	bool isJumping;
	bool isBottom;
	bool drawInRed = false;
	std::chrono::high_resolution_clock::time_point colorChangeStartTime;
	double redDurationInSeconds = 0.3;
public:
	Player(const class Game& mygame);
	void update() override;
	void draw() override;
	void init() override;
	float getPosY() { return pos_y; }
	float getPosX() { return pos_x; }
	void drawCollision(double durationInSeconds);
	Disk getCollisionHull() const override;
	float getRemainingLife() const { return life; }
	void drainLife(float amount) { life = std::max<float>(0.0f, life - amount); }

};