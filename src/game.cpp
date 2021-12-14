#include "game.h"
#include <SDL.h>
#include "controller.h"
#include <cmath>

Game::Game(std::size_t screenwidth, std::size_t screenheight) : slider_l(screenwidth, screenheight, (0), (screenheight/2)), slider_r(screenwidth, screenheight, (screenwidth-(screenwidth/50)), screenheight/2)
{
    screen_width = screenwidth;
    screen_height = screenheight;
    ball_width = screen_width/60;
    ball_height = screen_height/60;
    PlaceBall();    
}

void Game::Run(Controller &controller, Renderer &renderer, std::size_t targetFrameDuration)
{
    Uint32 titleTimeStamp = SDL_GetTicks();
    Uint32 frameStart;
    Uint32 frameEnd;
    Uint32 frameDuration = 0;

    int frameCount = 0;
    bool gameIsOn = true;
    while(gameIsOn)
    {
        frameStart = SDL_GetTicks();

        int isKeyPressed = controller.handleInput(gameIsOn, slider_l, slider_r);
        Update(isKeyPressed, ballpoint, frameDuration);
        renderer.Render(slider_l, slider_r, ballpoint);

        frameEnd = SDL_GetTicks();

        frameCount++;
        frameDuration = frameEnd - frameStart;

        //update windows title after 0.5 sec
        if(frameEnd - titleTimeStamp >= 500)
        {
            renderer.UpdateWindowTitle(score_l, score_r, frameCount);
            frameCount = 0;
            titleTimeStamp = frameEnd;
        }

        //if the frame duration is smaller than the target or desired frame duration then adjust the FPS by delay
        if(frameDuration < targetFrameDuration)
        {
            SDL_Delay(targetFrameDuration - frameDuration);
        }
    }
}

void Game::Update(int isKeyPressed, SDL_Point &ball, Uint32 frameduration)
{
    if(!isBallRolling) { return; }

    slider_l.Update(isKeyPressed, frameduration);
    slider_r.Update(isKeyPressed, frameduration);

    /*std::cout << "Frame Duration: " << frameduration << std::endl;
    if(balldirection == BallDirection::kleftup)
    {
        std::cout << "leftup" << ball.x << " " << ball.y << std::endl;
    }
    else if(balldirection == BallDirection::krightup)
    {
        std::cout << "rightup" << ball.x << " " << ball.y << std::endl;
    }
    else if(balldirection == BallDirection::kleftdown)
    {
        std::cout << "leftdown" << ball.x << " " << ball.y << std::endl;
    }
    else if(balldirection == BallDirection::krightdown)
    {
        std::cout << "rightdown" << ball.x << " " << ball.y << std::endl;
    }*/
    float speed_x;
    float speed_y;
    float dt = 1.0f;
    switch (balldirection)
    {
    case BallDirection::kleftup:
        speed_x = -speedball;
        speed_y = -speedball;
        ball.x += (speed_x * dt);
        ball.y += (speed_y * dt);
        break;
    case BallDirection::krightup:
        speed_x = speedball;
        speed_y = -speedball;
        ball.y += (speed_y * dt);
        ball.x += ceil(speed_x * dt);
        break;
    case BallDirection::kleftdown:
        speed_x = -speedball;
        speed_y = speedball;
        ball.x += (speed_x * dt);
        ball.y += ceil(speed_y * dt);
        break;
    case BallDirection::krightdown:
        speed_x = speedball;
        speed_y = speedball;
        ball.x += ceil(speed_x * dt);
        ball.y += ceil(speed_y * dt);
        break;
    }

    //updating direction for next loop
    //right slider contact
    if(ball.y >= slider_r.head_y && ball.y <= (slider_r.head_y + slider_r.slider_height) && (ball.x+ball_width) >= slider_r.head_x && balldirection == BallDirection::krightdown) 
    {
        balldirection = BallDirection::kleftdown;
    }
    else if(ball.y >= slider_r.head_y && ball.y <= (slider_r.head_y + slider_r.slider_height) && (ball.x+ball_width) >= slider_r.head_x && balldirection == BallDirection::krightup) 
    {
        balldirection = BallDirection::kleftup;
    }
    //left slider contact
    else if(ball.y >= slider_l.head_y && ball.y <= (slider_l.head_y + slider_l.slider_height) && ball.x <= (slider_l.head_x+slider_l.slider_width) && balldirection == BallDirection::kleftup)
    {
        balldirection = BallDirection::krightup;
    }
    else if(ball.y >= slider_l.head_y && ball.y <= (slider_l.head_y + slider_l.slider_height) && ball.x <= (slider_l.head_x+slider_l.slider_width) && balldirection == BallDirection::kleftdown)
    {
        balldirection = BallDirection::krightdown;
    }

    //ball penetrates or reached top wall
    if(ball.y <= 0 && ball.x > 0 && ball.x < screen_width && balldirection == BallDirection::krightup) {balldirection = BallDirection::krightdown;}
    else if(ball.y <= 0 && ball.x > 0 && ball.x < screen_width && balldirection == BallDirection::kleftup) {balldirection = BallDirection::kleftdown;}
    
    //ball penetrates or reached bottom wall
    if((ball.y+ball_height) >= screen_height && ball.x > 0 && ball.x < screen_width && balldirection == BallDirection::krightdown) {balldirection = BallDirection::krightup;}
    else if((ball.y+ball_height) >= screen_height && ball.x > 0 && ball.x < screen_width && balldirection == BallDirection::kleftdown) {balldirection = BallDirection::kleftup;}
    
    //ball penetrates beyond left slider and contacts the left wall
    if(((ball.y >= 0 && ball.y < slider_l.head_y) || (ball.y < screen_height && ball.y > (slider_l.head_y + slider_l.slider_height))) && ball.x < (slider_l.head_x+slider_l.slider_width)) 
    {
        isBallRolling = false;
    }
    //ball penetrates beyond right slider and contacts the right wall
    else if(((ball.y >= 0 && ball.y < slider_r.head_y) || (ball.y < screen_height && ball.y > (slider_r.head_y + slider_r.slider_height))) && ball.x > (slider_r.head_x))
    {
        isBallRolling = false;
    }

    //check if ball has successfully landed on the left slider and update score
    if(ball.y >= slider_l.head_y && ball.y <= (slider_l.head_y + slider_l.slider_height) && ball.x <= (slider_l.head_x+slider_l.slider_width))
    {
        score_l++;
    }

    //check if ball has successfully landed on the right slider and update score
    if(ball.y >= slider_r.head_y && ball.y <= (slider_r.head_y + slider_r.slider_height) && (ball.x+ball_width) >= slider_r.head_x)
    {
        score_r++;
    }
}

//function to place the ball initially on the screen
void Game::PlaceBall()
{
    ballpoint.x = screen_width / 2;
    ballpoint.y = screen_height / 2;
}

//funtions to retun score at the end of the game for each slider left and right respectively
int Game::getScoreLeft() { return score_l; }
int Game::getScoreRight() { return score_r; }