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

/**
*   @name Graphical Game Manager
*
*   It's main game class, connecting others classes representing pawns and main game manager.
*   Class is also responsible for display graphical content and handling mouse events.
*   To run this class u need to install lib SDL2.
*
*/

class Game{

public:
    ///Constructor
    Game();

    ///Desctuctor
    ~Game();

    /**
    *   Method initializing SDL and also display game window and create renderer.
    *
    *   @param title
    *   Title of new created window.
    *
    *   @param xPos
    *   Position on x axis of your display, where it will be displayed new created window.
    *
    *   @param yPos
    *   Position on y axis of your display, where it will be displayed new created window.
    *
    *   @param width
    *   Width of new created window.
    *
    *   @param height
    *   Height of new created window.
    *
    *   @param fullsreen
    *   If true window will be fullsreen.
    *
    */

    void init(const char* title, unsigned int xPos, unsigned int yPos, unsigned int width,
                unsigned int height, bool fullscreen);

    /**
    *    Method is responsible for handle mouse events, (only Left Click mouse).
    */

    void handleEvent();



    /**
    *   This method should be called in each frame,
    *   method is responsible for rendering gameboard and pwans in the game window.
    */

    void render();



    /**
    *   This method should be called in the end of program,
    *   method is responcible for destroy renderer, game window and quit SDL.
    */

    void clean();

    /**
    *   Method responcible for display promotion window
    *
    *   @param blackMove
    *   Flag that says which player is moving now. If black have movement true.
    *
    *   @param x
    *   Position of the pwan which reached the eight line. X axis.
    *
    *   @param y
    *   Position of the pwan which reached the eight line. Y axis.
    *
    */

    void pormotionPawn(bool blackMove, int x, int y);


    /**
    *   The method returns if the game has finished
    *
    *   @return
    *   Is game has finished.
    */

    bool isRunning();

private:
    ///Positon of auxiliary marker.
    int fieldPositionX, fieldPositionY;

    ///Flag that says is game end.
    bool runnging;
    ///Flag that says if there is a promotion.
    bool promotion;

    //SDL attributes
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Rect srcRect, destRect;

    SDL_Renderer *promotionRend;
    SDL_Window *promotionWin;

    ///Movement of auxiliary marker.
    void fieldSelectionMove(Sint32 x, Sint32 y);
    ///Private method for arranging figures.
    void startGame();
    ///Init promotion window.
    void promotionWindow();
    ///Promotion pawn and display texture of figure.
    void promotions(short int pawn);
};


#endif // GAME_H_INCLUDED
