#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "text.h"
#include "draw.h"
#include "common.h"
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

	int score;
	int highScore;

	bool isGameRunning;
	bool isGamePaused;

	void spawnFood();
	void eatFood(Snake* snake, Food* food);
	
	void checkCollisionWithEdges(Snake* snake);
	void checkCollisionWithTail(Snake* snake);
	void gameOver(Snake* snake);
	void restart();
};

