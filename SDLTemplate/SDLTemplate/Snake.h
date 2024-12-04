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
    void reset();

    bool addSegment;
    bool isCollidingWithTail();

    void setGameRunning(bool running);
private:
    SDL_Texture* headTexture;
    SDL_Texture* bodyTexture;
    SDL_Texture* tailTexture;

    SnakeBody initialPos;
    std::vector<SnakeBody> initialDirection;

    int x;
    int y;
    int w;
    int h;
    double angle;

    int size;
    int gridW;
    int gridH;

    bool isGameRunning;

    float updateTime;
    float currentUpdateTime;

    std::deque<SnakeBody> body;
    std::vector<SnakeBody> direction;
};

// could also do the tracking of tailmost, update, then add 