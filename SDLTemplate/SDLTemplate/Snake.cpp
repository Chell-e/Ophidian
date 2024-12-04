#include "Snake.h"

Snake::Snake()
{
	body.push_back({ gridW + 10, gridH + 10 }); // head
	body.push_back({ gridW + 9, gridH + 10 }); // body
	body.push_back({ gridW + 8, gridH + 10 }); // tail

	// body = (35, 35), (34, 35), (33, 35) co-ords
}

Snake::~Snake()
{

}

void Snake::start()
{
	// load texture
	texture = loadTexture("gfx/square.png");

	// initialize values
	w = 0;
	h = 0;

	size = 30;
	gridW = 25;
	gridH = 25;

	updateTime = 10;
	currentUpdateTime = 0;
	
	direction.push_back({ 1,0 });

	// query texture
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}

void Snake::update()
{
	if (currentUpdateTime > 0)
		currentUpdateTime--;

	if (currentUpdateTime == 0)
	{

		if (app.keyboard[SDL_SCANCODE_W] && direction[0].y != 1) // up
		{
			direction[0] = { 0, -1 };
		}

		if (app.keyboard[SDL_SCANCODE_S] && direction[0].y != -1) // down
		{
			direction[0] = { 0, 1 };
		}

		if (app.keyboard[SDL_SCANCODE_A] && direction[0].x != 1) // ;eft
		{
			direction[0] = { -1, 0 };
		}

		if (app.keyboard[SDL_SCANCODE_D] && direction[0].x != -1) // right
		{
			direction[0] = { 1, 0 };
		}

		SnakeBody head = body.front();

		head.x += direction[0].x;
		head.y += direction[0].y;

		body.pop_back(); // delete last element
		body.push_front(head); // add an element at the front

		currentUpdateTime = updateTime;
	}
}

void Snake::draw()
{
	for (int i = 0; i < body.size(); i++)
	{
		int x = body[i].x * size;
		int y = body[i].y * size;
		blit(texture, body[i].x * size, body[i].y * size);
	}
}

int Snake::getPositionX()
{ 
	SnakeBody head = body.front();

	return head.x;
}

int Snake::getPositionY()
{
	SnakeBody head = body.front();

	return head.y;
}
