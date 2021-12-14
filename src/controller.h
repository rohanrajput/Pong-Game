#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "slider.h"

class Controller
{
    public:
    Controller();
    int handleInput(bool &gameIsOn, Slider &slider_l, Slider &slider_r);
};

#endif