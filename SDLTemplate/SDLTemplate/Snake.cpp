#include "Snake.h"

Snake::Snake()
{
	initialPos = { gridW + 10, gridH + 10 };
	initialDirection.push_back({ 1,0 });

	body.push_back(initialPos); // head
	body.push_back({ gridW + 9, gridH + 10 }); // body
	body.push_back({ gridW + 8, gridH + 10 }); // tail

	direction = initialDirection;
	// body = (35, 35), (34, 35), (33, 35) co-ords
}

Snake::~Snake()
{

}

void Snake::start()
{
	// load texture
	texture = loadTexture("gfx/head.png");

	// initialize values
	w = 0;
	h = 0;

	size = 30;
	gridW = 25;
	gridH = 25;

	addSegment = false;
	isGameRunning = true;

	updateTime = 10;
	currentUpdateTime = 0;

	// query texture
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}

void Snake::update()
{
	if (isGameRunning)
	{
		return;
	}

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

		if (addSegment == true)
		{
			addSegment = false;
			body.push_front(head);
		}
		else
		{
			body.pop_back(); // delete last element
			body.push_front(head); // add an element at the front
		}

		currentUpdateTime = updateTime;
	}
}

void Snake::draw()
{
	//SDL_RenderCopyEx(app.renderer, texture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);

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

void Snake::reset()
{
	body.clear();

	body.push_back({ initialPos }); // head
	body.push_back({ gridW + 9, gridH + 10 }); // body
	body.push_back({ gridW + 8, gridH + 10 }); // tail

	direction = initialDirection;
	addSegment = false;

	isGameRunning = true; // added this
}

bool Snake::isCollidingWithTail()
{
	for (int i = 1; i < body.size(); i++)
	{
		if (body[0].x == body[i].x
			&& body[0].y == body[i].y)
		{
			return true;
		}
	}
	return false;
}

void Snake::setGameRunning(bool running)
{
	isGameRunning = running;
}

