#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "text.h"
#include "Snake.h"

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
};

