#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

class Food : public GameObject
{
public:
    Food();
    ~Food();

    void start();
    void update();
    void draw();

    void setPosition(int posX, int posY);

    int getPositionX();
    int getPositionY();

    int getWidth();
    int getHeight();
private:
    SDL_Texture* texture;

    int x;
    int y;
    int w;
    int h;

    int size;
    int gridW;
    int gridH;

};

