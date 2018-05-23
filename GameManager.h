#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED
#include "Pieces.h"

/**
*   @name Game Manager
*
*   This class is main game manager, it's responsible for representing chess board,
*   checking is King checkmate or whether the move the player wants to make is allowed.
*
*/

class GameManager{
    public:
        ///representation chess board.
        Pieces *board[8][8];

        ///constructor (@param game pointer to Game class)
        GameManager(Game *game);

        /**
        *   Method that tells whether a given move is allowed.
        *
        *   @param currentX
        *   Current position of fiugure we want to move. X axis.
        *
        *   @param currentY
        *   Current position of fiugure we want to move. Y axis.
        *
        *   @param targetX
        *   Position where we want to move our figure. X axis.
        *
        *   @param targetY
        *   Position where we want to move our figure. X axis.
        *
        *   @return
        *   Method returns flag (true if movement is allowed, false if is not).
        *
        */

        bool canMove(unsigned int currentX, unsigned int currentY, unsigned int targetX, unsigned int targetY);


        /**
        *   Method checks if King has a mat
        *
        *   @return
        *   Method returns flag (if king has a mat true).
        *
        */

        bool checkMate();

    private:
        /// that flag says which player is now moving.
        bool blackMove;
        /// Game class pointer, it's need to handle pormotion pawn.
        Game *game;

        /**
        *   method to standard changes in *board after player move,
        *   it's also checks if the pawn is on promotion line and evokes method from Game class.
        *
        *   @param currnetX
        *   Current position of fiugure we want to move. X axis.
        *
        *   @param currentY
        *   Current position of fiugure we want to move. Y axis.
        *
        *   @param targetX
        *   Position where we want to move our figure. X axis.
        *
        *   @param targetY
        *   Position where we want to move our figure. X axis.
        *
        */

        void makeMove(int currentX, int currentY, int targetX, int targetY);

        /**
        *   method returns bool which says if movement is allowed,
        *
        *   @param wsk
        *   pointer to figure we want to move.
        *
        *   @param x
        *   position of figure on board. X axis.
        *
        *   @param y
        *   position of figure on board. Y axis.
        *
        *   @return
        *   method return flag (true if move is allowed).
        *
        */

        bool move(Pieces* wks, int x, int y);

        /**
        *   method checks is king check in target position.
        *
        *   @param targetX
        *   target position (which field we want to check). X axis.
        *
        *   @param targetY
        *   target position (which field we want to check). Y axis.
        *
        *   @param blackTurn
        *   this flag says which king it is (if true is black king).
        *
        *   @param check
        *   this flag aunches additional method options that enter the place from
        *   which the king is being checked and who is checked him.
        *
        *   @return
        *   if king is checked in target position returns true.
        */

        bool canKingMove(int targetX, int targetY, bool blackTurn, bool check);

        /// method to checks is castle posible.
        bool castle(int rookX, int currentX, int currentY);
        /// method to checks is en passant is posible.
        bool enPassant(int currentX, int currentY, int targetX, int targetY);

};


#endif // GAMEMANAGER_H_INCLUDED
