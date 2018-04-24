#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED
#include "Pieces.h"


class GameManager{
    public:
        Pieces *board[8][8];

        GameManager();
        bool canMove(int8_t currentX, int8_t currentY, int8_t targetX, int8_t targetY);

    private:
        bool blackMove;
};


#endif // GAMEMANAGER_H_INCLUDED