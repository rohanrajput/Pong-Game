#ifndef SLIDER_H
#define SLIDER_H

#include <SDL.h>
#include <iostream>
#include <vector>

class Slider
{
    public:
    Slider(int screen_width, int screen_height, float head_x, float head_y);
    enum class Direction { kup, kdown, knochange };

    Direction direction = Direction::knochange;

    float speedslider{3.0f};
    float head_x;
    float head_y;
    int slider_width;
    int slider_height;
    int screen_w;
    int screen_h;

    void Update(int isKeyPressed, Uint32 frameduration);

    private:
    int grid_width;
    int grid_height;

    void UpdateHead(Uint32 frameduration);
};

#endif