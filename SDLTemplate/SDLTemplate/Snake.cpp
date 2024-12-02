#include "Snake.h"

Snake::Snake()
{
	headTexture = nullptr;
	tail = nullptr;
	cellSize = 20;
	currentDirection = Movement::UP;
}

Snake::~Snake()
{
	Node* current = head;
	while (current != nullptr)
	{
		Node* nextNode = current->next;
		delete current;
		current = nextNode;
	}
}

void Snake::start()
{
	// load head
	headTexture = loadTexture("gfx/head.png");
	bodyTexture = loadTexture("gfx/body.png");

	// initialize values
	x = 100;
	y = 100;
	width = 0;
	height = 0;

	cellSize = 20;
	
	// query texture to set width and height
	SDL_QueryTexture(headTexture, NULL, NULL, &width, &height);
	SDL_QueryTexture(bodyTexture, NULL, NULL, &width, &height);

	// initial snake
	addNode(100, 100);
	addNode(100, 150);
	addNode(100, 200);
}

void Snake::update()
{
	if (app.keyboard[SDL_SCANCODE_W]) // UP
	{
		changeDirection(Movement::UP);
		moveSnake();

	}

	if (app.keyboard[SDL_SCANCODE_S]) // DOWN
	{
		changeDirection(Movement::DOWN);
		moveSnake();

	}

	if (app.keyboard[SDL_SCANCODE_A]) // LEFT
	{
		changeDirection(Movement::LEFT);
		moveSnake();

	}

	if (app.keyboard[SDL_SCANCODE_D]) // RIGHT
	{
		changeDirection(Movement::RIGHT);
		moveSnake();

	}

}

void Snake::draw()
{
	Node* current = head;
	
	while (current != nullptr)
	{
		if (current == head)
		{
			blit(headTexture, current->position.x, current->position.y);
		}
		else
		{
			blit(bodyTexture, current->position.x, current->position.y);
		}
		current = current->next;
	}
}

void Snake::changeDirection(Movement direction)
{
	if ((currentDirection == Movement::UP && direction != Movement::DOWN) ||
		(currentDirection == Movement::DOWN && direction != Movement::UP) ||
		(currentDirection == Movement::LEFT && direction != Movement::RIGHT) ||
		(currentDirection == Movement::RIGHT && direction != Movement::LEFT)) {
		currentDirection = direction;
	}
}

void Snake::extendSnake()
{
	addNode(tail->position.x, tail->position.y);
}

void Snake::moveSnake()
{
	newHeadX = head->position.x;
	newHeadY = head->position.y;

	switch (currentDirection)
	{
	case Movement::UP:
		newHeadY -= cellSize;
		break;
	case Movement::DOWN:
		newHeadY += cellSize;
		break;
	case Movement::LEFT:
		newHeadX -= cellSize;
		break;
	case Movement::RIGHT:
		newHeadX += cellSize;
		break;
	}

	addNode(newHeadX, newHeadY);
	removeNode();
}

void Snake::addNode(int x, int y)
{
	Node* newNode = new Node();
	newNode->position = { x, y, cellSize, cellSize };
	newNode->next = nullptr;
	
	if (tail != nullptr)
	{ 
		tail->next = newNode;
	}

	tail = newNode;

	if (head == nullptr)
	{
		head = newNode;
	}
}

void Snake::removeNode()
{
	if (head == nullptr)
		return;

	if (head == tail)
	{
		delete head;
		head = tail = nullptr;
		return;
	}

	Node* current = head;
	while (current->next != tail)
	{
		current = current->next;
	}

	delete tail;
	tail = current;
	tail->next = nullptr;
}

