#include "sgg/graphics.h"
#include "defines.h"
#include <string>
#include "game.h"

void draw() 
{
	Game* game = reinterpret_cast<Game*> (graphics::getUserData());
	game->draw();

}


void update(float ms)
{
	Game* game = reinterpret_cast<Game*> (graphics::getUserData());
	game->update();
}

void resize(int w, int h)
{
	Game* game = reinterpret_cast<Game*> (graphics::getUserData());
	game->setWindowDimensions((unsigned int)w, (unsigned int)h);
}


int main(int argc, char** argv)
{

	Game mygame;

	graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MyProject");

	graphics::setUserData(&mygame);

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::setCanvasSize(CANVAS_WIDTH,CANVAS_HEIGHT);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	mygame.init();
	graphics::startMessageLoop();

	return 0;
}