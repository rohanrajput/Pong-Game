#include <iostream>
#include "game.h"
#include "controller.h"
#include "renderer.h"

int main(int agrv, char** agrs) {
    constexpr std::size_t kFramesPerSecond{ 60 };
    constexpr std::size_t kMsPerFrame{ 1000 / kFramesPerSecond };
    constexpr std::size_t kScreenWidth{ 300 };
    constexpr std::size_t kScreenHeight{ 300 };
    constexpr std::size_t kGridWidth{ 32 };
    constexpr std::size_t kGridHeight{ 32 };

    Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    Controller controller{};
    Game game(kScreenWidth, kScreenHeight);
    game.Run(controller, renderer, kMsPerFrame);

    std::cout << "Left Score: " << game.getScoreLeft() << std::endl;
    std::cout << "Right Score: " << game.getScoreRight() << std::endl;
    return 0;
}
