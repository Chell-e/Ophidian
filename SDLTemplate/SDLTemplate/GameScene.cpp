#include "GameScene.h"

GameScene::GameScene()
{
	score = 0;
	highScore = 0;

	// Register and add game objects on constructor
	snake = new Snake();
	this->addGameObject(snake);
}

GameScene::~GameScene()
{
	delete snake;

	for (int i = 0; i < spawnedFoods.size(); i++)
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

	isGameRunning = false;
	isGamePaused = true;

	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);
	
	initFonts(); 
}

void GameScene::draw()
{
	SDL_RenderCopy(app.renderer, texture, &src, &dest);

	Scene::draw();
	
	drawText(100, 10, 600, 255, 255, TEXT_CENTER, "SCORE: %03d", score);
	drawText(600, 10, 700, 255, 255, TEXT_CENTER, "HIGH SCORE: %03d", highScore);
	if (isGamePaused)
	{
		drawText(SCREEN_WIDTH / 2, 600, 255, 255, 255, TEXT_CENTER, "PRESS SPACE TO START");
	}	
}

void GameScene::update()
{
	Scene::update();

	if (isGameRunning)
	{
		if (spawnedFoods.empty())
		{
			spawnFood();
		}

		for (int i = 0; i < spawnedFoods.size(); i++)
		{
			eatFood(snake, food);
		}

		checkCollisionWithEdges(snake);
		checkCollisionWithTail(snake);

		if (app.keyboard[SDL_SCANCODE_SPACE])
		{
			isGamePaused = false;
			snake->setGameRunning(false);
		}
	}
	isGameRunning = true;

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
		score += 10;

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

void GameScene::checkCollisionWithEdges(Snake* snake)
{
	if (snake->getPositionX() == gridW || snake->getPositionX() == -1 ||
		snake->getPositionY() == gridH || snake->getPositionY() == -1)
	{
		gameOver(snake);
	}
}

void GameScene::checkCollisionWithTail(Snake* snake)
{
	if (snake->isCollidingWithTail())
	{
		gameOver(snake);
	}
}

void GameScene::gameOver(Snake* snake)
{
	snake->reset();

	for (int i = 0; i < spawnedFoods.size(); i++)
	{	
		delete spawnedFoods[i];
	}
	spawnedFoods.clear();

	restart();
}

void GameScene::restart()
{
	if (score > highScore)
	{
		highScore = score;
	}
	score = 0;

	isGameRunning = true;
	isGamePaused = true;

	spawnFood();
}
