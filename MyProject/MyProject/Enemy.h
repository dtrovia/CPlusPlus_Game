#pragma once
#include "gameobject.h"
#include "sgg/graphics.h"

class Enemy : public GameObject, public Collidable
{
	float speed;
	float size;
	float rotation;
	float pos_x, pos_y;
	graphics::Brush brush;
	bool active = true;
	Enemy* enemy = nullptr;
	float life = 1.0f;
	bool enemy_initialized = false;

public:
	void update() override;
	void draw() override;
	void init() override;
	bool isActive() { return active; }
	Enemy(const class Game& mygame);
	~Enemy();
	Disk getCollisionHull() const override;
	float getRemainingLife() const { return life; }
	void drainLife(float amount) { life = std::max<float>(0.0f, life - amount/size*200.0f); }
	void setEnemyLife(float life) { float enemy_life = life; }
};