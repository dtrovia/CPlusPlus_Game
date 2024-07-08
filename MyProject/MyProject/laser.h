#pragma once
#include "gameobject.h"
#include "defines.h"
#include "gameobject.h"

class Laser : public GameObject, public Collidable {
	
	float speed;
	float size;
	bool active = true;
	Laser * laser= nullptr;
	bool laser_initialized = false;

public:
	Laser(const class Game& mygame);
	~Laser();
	void update() override;
	void draw() override;
	void init();
	bool isActive() { return active; }
	float getPosY() { return laser_pos_y; }
	float getPosX() { return laser_pos_x; }
	Disk getCollisionHull() const override;
	bool visible = false;
	float laser_pos_x, laser_pos_y;
};

