#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "controller.h"
#include "slider.h"
#include "renderer.h"
#include <SDL.h>

class Game
{
    public:
    Game(std::size_t screenwidth, std::size_t screenheight);
    void Run(Controller &controller, Renderer &renderer, std::size_t targetFrameDuration);
    void Update(int isKeyPressed, SDL_Point &ball, Uint32 framesDuration);
    int getScoreLeft();
    int getScoreRight();
    
    int score_l {0};
    int score_r {0};

    SDL_Point ballpoint;

    private:
    int grid_width;
    int grid_height;
    int screen_width;
    int screen_height;
    Slider slider_l;
    Slider slider_r;
    void PlaceBall();

    enum class BallDirection { kleftup, kleftdown, krightup, krightdown };
    BallDirection balldirection = BallDirection::kleftup;
    float speedball{1.0f};
    bool isBallRolling {true};
    int ball_height;
    int ball_width;
};

#endif