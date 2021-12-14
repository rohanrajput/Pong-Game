#include "renderer.h"
#include <SDL.h>
#include <iostream>
#include "slider.h"

Renderer::Renderer(std::size_t screenwidth, std::size_t screenheight, std::size_t gridwidth, std::size_t gridheight) : screen_width(screenwidth), screen_height(screenheight), grid_width(gridwidth), grid_height(gridheight)
{
    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized" << std::endl;
        std::cout << "SDL error" << SDL_GetError() << std::endl;
    }

    //Create window
    window = SDL_CreateWindow("Slider game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);
    if(nullptr == window)
    {
        std::cout << "Window could be created" << std::endl;
        std::cout << "SDL error" << SDL_GetError() << std::endl;
    }

    //create renderer
    sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(nullptr == sdl_renderer)
    {
        std::cout << "Renderer could be created" << std::endl;
        std::cout << "SDL error" << SDL_GetError() << std::endl;
    }
}

Renderer::~Renderer()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::Render(Slider slider_l, Slider slider_r, SDL_Point &ball)
{
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;

    //clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    //Render left slider body
    SDL_Rect sliderbody_l;
    sliderbody_l.w = slider_l.slider_width;
    sliderbody_l.h = slider_l.slider_height;
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    sliderbody_l.x = slider_l.head_x;
    sliderbody_l.y = slider_l.head_y;
    SDL_RenderFillRect(sdl_renderer, &sliderbody_l);

    //Render right slider body
    SDL_Rect sliderbody_r;
    sliderbody_r.w = slider_r.slider_width;
    sliderbody_r.h = slider_r.slider_height;
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    sliderbody_r.x = slider_r.head_x;
    sliderbody_r.y = slider_r.head_y;
    SDL_RenderFillRect(sdl_renderer, &sliderbody_r);

    //Render ball
    SDL_Rect ballbody;
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    ballbody.w = screen_width/60;
    ballbody.h = screen_width/60;
    ballbody.x = ball.x;
    ballbody.y = ball.y;
    SDL_RenderFillRect(sdl_renderer, &ballbody);

    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score_l, int score_r, int fps)
{
    std::string title{"Left Score: " + std::to_string(score_l) + " Right Score: " + std::to_string(score_r) + " FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(window, title.c_str());
}