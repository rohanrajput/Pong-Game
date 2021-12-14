#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include "slider.h"

class Renderer
{
    public:
    Renderer(std::size_t screenwidth, std::size_t screenheight, std::size_t gridwidth, std::size_t gridheight);
    ~Renderer();

    void Render(Slider slider_l, Slider slider_r, SDL_Point &ball);
    void UpdateWindowTitle(int score_l, int score_r, int fps);

    private:
    std::size_t screen_width;
    std::size_t screen_height;
    std::size_t grid_width;
    std::size_t grid_height;

    SDL_Window *window;
    SDL_Renderer *sdl_renderer;
};

#endif