#ifndef PIECES_H_INCLUDED
#define PIECES_H_INCLUDED

#include "Game.h"

typedef std::array<std::vector<std::pair<int, int>>, 8> movements;

/**
*   This abstract class representing all figures of chess.
*   It has all cammon attribute and methods.
*
*   Children of this class:
*   #King
*   #Queen
*   #Bishop
*   #Rook
*   #Horse
*   #Pawn
*/

class Pieces{
    public:
        /// position on the game board.
        int boardX, boardY;
        /// color of the figure.
        bool black;

        /**
        *   Constructor
        *
        *   @param xPos
        *   positon on board. X axis.
        *
        *   @param yPos
        *   positon on board. X axis.
        *
        *   @param texture
        *   path to figure texture.
        *
        *   @param renderer
        *   pointer to SDL_Renderer.
        *
        *   @param black
        *   color of the figure.
        *
        */

        Pieces(int xPos, int yPos, const char* texture, SDL_Renderer *renderer, bool black);

        /**
        *   this method returns all movements which are available for a given figure.
        *
        *   @param blackMove
        *   which player is now moving (if ture black moves).
        *
        *   @return
        *   method returns all movement. type: std::array<std::vector<std::pair<int, int>>, 8>
        */

        virtual movements move(bool blackMove) = 0;

        /// This method update position of figure texture.
        virtual void update() = 0;
        /// This method render figure texture.
        virtual void render() = 0;
        /// This method destroys figure.
        virtual void destroy() = 0;
        /// This method change the first move flag.
        virtual void isMoved() = 0;

        /// This method change positon of figure texture when player click left button (x, y) position.
        void grab(Sint32 x, Sint32 y);

    protected:
        /// position of figure texture on window.
        int xPos, yPos;
        /// weight of figure
        int weight;

        // SDL attributes
        SDL_Texture *objTexture;
        SDL_Rect srcRect, destRect;
        SDL_Renderer* renderer;
};

class King: public Pieces{
    public:
        /// direction from which the king is checked.
        int checkX, checkY;
        /// position of the figure which is checked king.
        int whoCheckX, whoCheckY;

        King(int xPos, int yPos, const char* texture, SDL_Renderer *renderer, bool black);
        ~King();

        virtual std::array<std::vector<std::pair<int, int>>, 8> move(bool blackMove);
        virtual void update();
        virtual void render();
        virtual void destroy();
        virtual void isMoved();

        /// this method @return makedMoved flag.
        bool makedMove();

    private:
        /// first move flag.
        bool makedMoved;
};

class Queen: public Pieces{
    public:
        Queen(int xPos, int yPos, const char* texture, SDL_Renderer *renderer, bool black);
        ~Queen();

        virtual std::array<std::vector<std::pair<int, int>>, 8> move(bool blackMove);
        virtual void update();
        virtual void render();
        virtual void destroy();
        virtual void isMoved();
};

class Bishop: public Pieces{
    public:
        Bishop(int xPos, int yPos, const char* texture, SDL_Renderer *renderer, bool black);
        ~Bishop();

        virtual std::array<std::vector<std::pair<int, int>>, 8> move(bool blackMove);
        virtual void update();
        virtual void render();
        virtual void destroy();
        virtual void isMoved();
};

class Horse: public Pieces{
    public:
        Horse(int xPos, int yPos, const char* texture, SDL_Renderer *renderer, bool black);
        ~Horse();

        virtual std::array<std::vector<std::pair<int, int>>, 8> move(bool blackMove);
        virtual void update();
        virtual void render();
        virtual void destroy();
        virtual void isMoved();
};

class Rook: public Pieces{
    public:
        Rook(int xPos, int yPos, const char* texture, SDL_Renderer *renderer, bool black);
        ~Rook();

        virtual std::array<std::vector<std::pair<int, int>>, 8> move(bool blackMove);
        virtual void update();
        virtual void render();
        virtual void destroy();
        virtual void isMoved();

        /// this method @return makedMoved flag.
        bool makedMove();

    private:
        /// first move flag.
        bool makedMoved;
};

class Pawn: public Pieces{
    public:
        Pawn(int xPos, int yPos, const char* texture, SDL_Renderer *renderer, bool black);
        ~Pawn();

        virtual std::array<std::vector<std::pair<int, int>>, 8> move(bool blackMove);
        virtual void update();
        virtual void render();
        virtual void destroy();
        virtual void isMoved();

        /// this method @return makedMoved flag.
        bool makedMove();

    private:
        /// first move flag.
        bool makedMoved;
};

#endif // PIECES_H_INCLUDED
