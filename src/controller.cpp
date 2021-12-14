#include "controller.h"
#include "SDL.h"

Controller::Controller() {}

int Controller::handleInput(bool &gameIsOn, Slider &slider_l, Slider &slider_r)
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
        {
            gameIsOn = false;
        }
        else if(e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_w:
                slider_l.direction = Slider::Direction::kup;
                break;
            case SDLK_s:
                slider_l.direction = Slider::Direction::kdown;
                break;
            }
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                slider_r.direction = Slider::Direction::kup;
                break;
            case SDLK_DOWN:
                slider_r.direction = Slider::Direction::kdown;
                break;
            }
        }
        else if(e.type == SDL_KEYUP)
        {
            if(e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_s)
            {
                slider_l.direction = Slider::Direction::knochange;
            }

            if(e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_DOWN)
            {
                slider_r.direction = Slider::Direction::knochange;
            }
        }
    }
    return SDL_PollEvent(&e);
}