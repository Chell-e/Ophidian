#include "Food.h"

Food::Food()
{

}

Food::~Food()
{
}

void Food::start()
{
	//x = gridW + 3;
	//y = gridH + 3;
	w = 0;
	h = 0;

	size = 30;
	gridW = 25;
	gridH = 25;

	texture = loadTexture("gfx/food.png");

	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}

void Food::update()
{
}

void Food::draw()
{
	blit(texture, x * size, y * size);
}

void Food::setPosition(int posX, int posY)
{
	this->x = posX;
	this->y = posY;
}

int Food::getPositionX()
{
	return x;
}

int Food::getPositionY()
{
	return y;
}

int Food::getWidth()
{
	return w;
}

int Food::getHeight()
{
	return h;
}
