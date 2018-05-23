#include <cstdlib>
#include <chrono>
#include <iostream>
#include <thread>
#include "Game.h"

/**
*    @name neural network chess player
*
*    This program is implementation of computer chess player, program use neural networks.
*    Code was written to needs BA dissertation.
*    Program doesn't have any copyrights.
*
*    @author Adam Wójcik
*
*    2018
*/

Game *game = nullptr;

typedef std::chrono::high_resolution_clock Time;

long getMilliseconds(auto time);

int main()
{
    game = new Game();
    game -> init("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 854, 854, false);

    auto lastLoopTime = Time::now();
    const int TARGET_FPS = 30;
    const long OPTIMAL_TIME = 1000000000 / TARGET_FPS;

    double lastFpsTime = 0;
    int fps = 0;

    while(game -> isRunning()){
        auto now = Time::now();
        long updateLenght = getMilliseconds(now) - getMilliseconds(lastLoopTime);
        lastLoopTime = now;

        lastFpsTime += updateLenght;
        fps++;

        if(lastFpsTime >= 1000000){
            #ifdef WINDOWS
                std::system("cls");
            #else
                std::system("clear");
            #endif // WINDOWS

            std::cout << "FPS: " << fps << std::endl;
            lastFpsTime = 0;
            fps = 0;
        }
        game -> handleEvent();
        //game -> update();
        game -> render();

        std::this_thread::sleep_for(std::chrono::milliseconds((getMilliseconds(lastLoopTime) - getMilliseconds(Time::now()) + OPTIMAL_TIME)/1000000));
    }

    game -> clean();

    return EXIT_SUCCESS;
}

long getMilliseconds(auto time){
    auto now_ms = std::chrono::time_point_cast<std::chrono::microseconds>(time);
    auto value = now_ms.time_since_epoch();
    long duration = value.count();

    return duration;
}
