#include "Snake.h"

Snake::Snake()
{
	body.push_back({ gridW/ 2, gridH / 2 });
	body.push_back({ gridW / 2 + 1, gridH / 2 });
	body.push_back({ gridW / 2 - 2, gridH / 2 });
}

Snake::~Snake()
{

}

void Snake::start()
{
	// load texture
	texture = loadTexture("gfx/square.png");

	// initialize values
	x = 200;
	y = 200;
	w = 0;
	h = 0;
	size = 32;
	gridW = 40;
	gridH = 32;

	// query texture
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}

void Snake::update()
{
	SnakeBody head = body[0];

	if (app.keyboard[SDL_SCANCODE_W]) // UP
	{
		head.y -= 1;
	}

	if (app.keyboard[SDL_SCANCODE_S]) // DOWN
	{
		head.y += 1;
	}

	if (app.keyboard[SDL_SCANCODE_A]) // LEFT
	{
		head.x -= 1;
	}

	if (app.keyboard[SDL_SCANCODE_D]) // RIGHT
	{
		head.x += 1;
	}

	for (int i = body.size() - 1; i > 0; --i)
	{
		body[i] = body[i - 1];  
	}

	body[0] = head;
}

void Snake::draw()
{
	for (const auto& segment : body)
	{
		blit(texture, segment.x * size, segment.y * size);
	}

}
