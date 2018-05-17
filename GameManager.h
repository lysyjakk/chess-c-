#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED
#include "Pieces.h"


class GameManager{
    public:
        Pieces *board[8][8];

        GameManager(Game *game);
        bool canMove(int currentX, int currentY, int targetX, int targetY);
        bool checkMate();
        void makeMove(int currentX, int currentY, int targetX, int targetY);

    private:
        bool blackMove;
        Game *game;

        bool move(Pieces* wks, int x, int y);
        bool canKingMove(int targetX, int targetY, bool blackTurn, bool check);
        bool castle(int rookX, int currentX, int currentY);
        bool enPassant(int currentX, int currentY, int targetX, int targetY);
};


#endif // GAMEMANAGER_H_INCLUDED
