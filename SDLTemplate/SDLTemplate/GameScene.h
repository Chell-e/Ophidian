#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "text.h"

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

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Color gridLine;

	int cellSize;
	int gridWidth;
	int gridHeight;

	int windowWidth;
	int windowHeight;
};

