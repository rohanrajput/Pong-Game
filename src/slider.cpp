#include "slider.h"
#include <cmath>
#include <vector>
#include <iostream>

Slider::Slider(int screen_width, int screen_height, float head_x, float head_y) : head_x(head_x), head_y(head_y)
{
    screen_w = screen_width;
    screen_h = screen_height;
    slider_width = screen_width/50;
    slider_height = screen_height/5;
}

void Slider::Update(int isKeyPressed, Uint32 frameduration)
{
    UpdateHead(frameduration);
}

void Slider::UpdateHead(Uint32 frameduration)
{
    float speed;
    switch (direction)
    {
    case Direction::kup:
        speed = -speedslider;
        head_y += (speed * frameduration);
        break;
    case Direction::kdown:
        speed = speedslider;
        head_y += (speed * frameduration);
        break;
    case Direction::knochange:
        head_y = head_y;
        break;
    }

    if(head_y <= 0)
    {
        head_y = 0;
    }
    else if(head_y >= (screen_h - slider_height))
    {
        head_y = (screen_h - slider_height);
    }
}