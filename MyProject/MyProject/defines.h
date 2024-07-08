#pragma once
#include <random>

#define CANVAS_WIDTH 1200
#define CANVAS_HEIGHT 500
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600

#define ASSET_PATH ".\\assets\\"

float rand0to1();

struct Disk
{
	float cx, cy;
	float radius;
};