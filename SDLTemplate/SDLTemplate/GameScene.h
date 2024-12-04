#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "text.h"
#include "Snake.h"
#include "Food.h"
#include <vector>

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	void start();
	void draw();
	void update();

private:
	SDL_Texture* texture;
	SDL_Rect src;
	SDL_Rect dest;

	Snake* snake;
	Food* food;

	std::vector<Food*> spawnedFoods;

	int size;
	int gridW;
	int gridH;

	void spawnFood();
	void eatFood(Snake* snake, Food* food);
};

