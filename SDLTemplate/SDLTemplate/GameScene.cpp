#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	snake = new Snake();
	this->addGameObject(snake);

	food = NULL;
	hasFoodSpawned = false;
}

GameScene::~GameScene()
{
	delete snake;
	delete food;
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


	spawnFood();
}

void GameScene::spawnFood()
{
	if (!hasFoodSpawned)
	{
		food = new Food();
		this->addGameObject(food);

		food->setPosition(rand() % gridW, rand() % gridH);

		hasFoodSpawned = true;
	}
}

