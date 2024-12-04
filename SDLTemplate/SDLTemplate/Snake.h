// Snake.h
#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include <vector>
#include <deque>

struct SnakeBody
{
    int x;
    int y;
};

class Snake : public GameObject
{
public:
    Snake();
    ~Snake();

    void start();
    void update();
    void draw();

    int getPositionX();
    int getPositionY();

    bool addSegment;

private:
    SDL_Texture* texture;

    int x;
    int y;
    int w;
    int h;

    int size;
    int gridW;
    int gridH;

    float updateTime;
    float currentUpdateTime;

    std::deque<SnakeBody> body;
    std::vector<SnakeBody> direction;
};

// keep track of coordinates, when to make it a rectangle 