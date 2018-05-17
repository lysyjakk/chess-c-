#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glu.h>
#include <vector>
#include <array>
#include <typeinfo>

class Game{

public:
    Game();
    ~Game();

    void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
    void handleEvent();
    void update();
    void render();
    void clean();
    void pormotionPawn(bool blackMove, int x, int y);
    bool isRunning();

private:
    int fieldPositionX, fieldPositionY;

    bool runnging;
    bool promotion;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Rect srcRect, destRect;

    SDL_Renderer *promotionRend;
    SDL_Window *promotionWin;

    void fieldSelectionMove(Sint32 x, Sint32 y);
    void startGame();
    void promotionWindow();
    void promotions(short int pawn);
};


#endif // GAME_H_INCLUDED
