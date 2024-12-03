#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "text.h"
#include "Snake.h"
#include "Food.h"

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

	int size;
	int gridW;
	int gridH;
	bool hasFoodSpawned;

	void spawnFood();
};

