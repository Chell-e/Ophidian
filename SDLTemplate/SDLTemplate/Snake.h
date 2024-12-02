#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include <list> 

enum class Movement
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct Node
{
	SDL_Rect position;
	Node* next;
};

class Snake : public GameObject
{
public:
	Snake();
	~Snake();

	void start();
	void update();
	void draw();

	void changeDirection(Movement direction);
	void extendSnake();
	void moveSnake();

	void addNode(int x, int y);
	void removeNode();
private:
	SDL_Texture* headTexture;
	SDL_Texture* bodyTexture;
	Movement currentDirection;

	int x;
	int y;
	int width;
	int height;

	int newHeadX;
	int newHeadY;

	int cellSize;
	
	Node* head;
	Node* tail;
};

