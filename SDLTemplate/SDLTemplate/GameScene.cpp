#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	snake = new Snake();
	this->addGameObject(snake);
}

GameScene::~GameScene()
{
	delete snake;

	for (int i = 0; spawnedFoods.size(); i++)
	{
		delete spawnedFoods[i];
	}
	spawnedFoods.clear();
}
 void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here

	texture = loadTexture("gfx/background.png");

	src.w = 900;
	src.h = 900;

	dest.w = SCREEN_WIDTH;
	dest.h = SCREEN_HEIGHT;

	size = 30;
	gridW = 25;
	gridH = 25;

	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);
}

void GameScene::draw()
{
	SDL_RenderCopy(app.renderer, texture, &src, &dest);

	Scene::draw();
}

void GameScene::update()
{
	Scene::update();

	if (spawnedFoods.empty())
	{
		spawnFood();
	}

	for (int i = 0; i < spawnedFoods.size(); i++)
	{
		eatFood(snake, food);
	}
}


void GameScene::spawnFood()
{
	int x = rand() % gridW;
	int y = rand() % gridH;

	food = new Food();
	this->addGameObject(food);

	food->setPosition(x, y);
	spawnedFoods.push_back(food);
}

void GameScene::eatFood(Snake* snake, Food* food)
{
	if (snake->getPositionX() == food->getPositionX() && snake->getPositionY() == food->getPositionY())
	{	
		snake->addSegment = true;

		int index = -1;

		for (int i = 0; i < spawnedFoods.size(); i++)
		{
			if (food == spawnedFoods[i])
			{
				index = i;
				break;
			}
		}

		if (index != -1)
		{
			spawnedFoods.erase(spawnedFoods.begin() + index);
			delete food;
		}
	}
}
