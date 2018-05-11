#ifndef PIECES_H_INCLUDED
#define PIECES_H_INCLUDED

#include "Game.h"

typedef std::array<std::vector<std::pair<int, int>>, 8> movements;

class Pieces{
    public:
        int8_t boardX, boardY;
        bool black;

        Pieces(int xPos, int yPos, const char* texture, SDL_Renderer *renderer, bool black);

        virtual movements move(bool blackMove) = 0;
        virtual void update() = 0;
        virtual void render() = 0;
        virtual void destroy() = 0;
        virtual void isMoved() = 0;

        void grab(Sint32 x, Sint32 y);

    protected:
        int xPos, yPos;
        int8_t weight;

        SDL_Texture *objTexture;
        SDL_Rect srcRect, destRect;
        SDL_Renderer* renderer;
};

class King: public Pieces{
    public:
        King(int xPos, int yPos, const char* texture, SDL_Renderer *renderer, bool black);
        ~King();

        virtual std::array<std::vector<std::pair<int, int>>, 8> move(bool blackMove);
        virtual void update();
        virtual void render();
        virtual void destroy();
        virtual void isMoved();

        bool makedMove();

    private:
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

        bool makedMove();

    private:
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

        bool makedMove();

    private:
        bool makedMoved;
};

#endif // PIECES_H_INCLUDED
