#include "GameManager.h"

Pieces* lastMovedPawn;


GameManager::GameManager(){
    blackMove = false;
}

bool GameManager::canMove(int8_t currentX, int8_t currentY, int8_t targetX, int8_t targetY){

    if(board[currentY][currentX] -> black == blackMove){

        movements v;

        bool flag = true;

        v = board[currentY][currentX] -> move(blackMove);

        if(!v.empty()){

            if(typeid(*board[currentY][currentX]) == typeid(King)){
                King* king = (King*)board[currentY][currentX];

                if(!canKingMove(targetX, targetY, blackMove,  false))
                    flag = false;

                if((targetX == 6 || targetX == 2) && !king -> makedMove() && flag){
                    int8_t rookX = targetX == 6 ? 7 : 0;

                    if(typeid(*board[currentY][rookX]) == typeid(Rook)){
                        Rook* rook = (Rook*)board[currentY][rookX];

                            if(!rook -> makedMove()){
                                if(castle(rookX, currentX, currentY)){
                                    blackMove ^= true;
                                    return true;
                                }
                            }
                    }
                }
            }

            for(int i = 0; i < 8; i++){
                for(int k = 0; k < v[i].size(); k++){

                    if(v[i][k].first == targetX && v[i][k].second == targetY){

                        for(int g = 0; g < k; g++){
                            if(board[v[i][g].second][v[i][g].first] != nullptr)
                                flag = false;
                        }

                        if(board[targetY][targetX] != nullptr && flag){
                            if(!((board[targetY][targetX] -> black && !blackMove) ||
                                (!board[targetY][targetX] -> black && blackMove)))
                                    flag = false;
                        }

                        if(typeid(*board[currentY][currentX]) == typeid(Pawn) && flag){

                            if(i == 0){
                                if(blackMove){
                                    if(currentY + 1 < 8){
                                        if(board[currentY + 1][currentX] != nullptr)
                                            flag = false;
                                    }
                                } else {
                                    if(currentY - 1 >= 0){
                                        if(board[currentY - 1][currentX] != nullptr)
                                            flag = false;
                                    }
                                }
                            }
                            else if(i != 0){
                                if(blackMove){
                                    if(board[v[i][0].second][v[i][0].first] == nullptr ? true : board[v[i][0].second][v[i][0].first] -> black)
                                            flag = false;
                                } else {
                                    if(board[v[i][0].second][v[i][0].first] == nullptr ? true : !board[v[i][0].second][v[i][0].first] -> black)
                                            flag = false;
                                }

                                if(enPassant(currentX, currentY, targetX, targetY, v))
                                    flag = true;

                            }
                        }

                        if(flag){
                            if(typeid(*board[currentY][currentX]) == typeid(Pawn) && !((Pawn*)board[currentY][currentX]) -> makedMove()){
                                lastMovedPawn = (Pawn*)board[currentY][currentX];
                            }
                            else
                                lastMovedPawn = nullptr;

                            if(board[targetY][targetX] != nullptr)
                                board[targetY][targetX] -> destroy();

                            blackMove ^= true;
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}

bool GameManager::canKingMove(int8_t targetX, int8_t targetY, bool blackTurn, bool check){
    movements v;
    bool freeField = true;
    bool breakLoops = false;

    try{
        for(int i = 0; i < 8; i++){
            for(int k = 0; k < 8; k++){

                if(board[i][k] == nullptr) continue;
                else if(board[i][k] -> black != blackTurn){
                    v = board[i][k] -> move(!blackTurn);

                    if(!v.empty()){

                        for(int g = 0; g < v.size(); g++){

                            if(v[g].empty()) continue;

                            for(int p = 0; p < v[g].size(); p++){

                                if(v[g][p].first == targetX && v[g][p].second == targetY){

                                    if(typeid(*board[i][k]) == typeid(Pawn) && g == 0) continue;
                                    bool flag = true;

                                    for(int r = 1; r < p; r++){
                                        if(board[v[g][r].second][v[g][r].first] != nullptr &&
                                            typeid(*board[v[g][r].second][v[g][r].first]) != typeid(King)){
                                            flag = false;

                                            break;
                                        }
                                    }

                                    if(flag){

                                        if(check){
                                            King *king = (King*)board[targetY][targetX];
                                            king -> checkX = v[g][p - 1].first;
                                            king -> checkY = v[g][p - 1].second;
                                        }

                                        breakLoops = true;
                                        throw breakLoops;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    } catch(bool breakLoops){
        if(breakLoops)
            freeField = false;
    }

    return freeField;
}

bool GameManager::castle(int8_t rookX, int8_t currentX, int8_t currentY){

    /* Roszada */

    bool flag = true;

    if(rookX == 0)
    {
        for(int g = currentX - 2; g > rookX; g--)
        {
            if(board[currentY][g] != nullptr) flag = false;
        }
    }
    else {
        for(int g = currentX + 1; g < rookX; g++)
        {
            if(board[currentY][g] != nullptr) flag = false;
        }
    }

    if(flag)
    {
        if(rookX == 7)
        {
            board[currentY][rookX] -> grab((Sint32)((5 * 100) + 72), (Sint32)((currentY * 100) + 72));
            makeMove(rookX, currentY, 5, currentY);
        }
        else
        {
            board[currentY][rookX] -> grab((Sint32)((3 * 100) + 72), (Sint32)((currentY * 100) + 72));
            makeMove(rookX, currentY, 3, currentY);
        }
    }

    return flag;
}

bool GameManager::enPassant(int8_t currentX, int8_t currentY, int8_t targetX, int8_t targetY, movements v){

    /* Bicie w przelocie */

    bool flag = false;

    if(blackMove){
        if((currentX + 1 < 8 && currentX - 1 >= 0) && currentY == 4)
        {
            if(board[currentY][currentX + 1] == lastMovedPawn &&
            targetX == v[1][0].first && targetY == v[1][0].second &&
            board[currentY][currentX + 1] != nullptr)
            {
                flag = true;
                board[currentY][currentX + 1] -> destroy();
                board[currentY][currentX + 1] = nullptr;
            }
            else if(board[currentY][currentX - 1] == lastMovedPawn &&
            targetX == v[2][0].first && targetY == v[2][0].second &&
            board[currentY][currentX - 1] != nullptr)
            {
                flag = true;
                board[currentY][currentX - 1] -> destroy();
                board[currentY][currentX - 1] = nullptr;
            }
        }
    } else {
        if((currentX + 1 < 8 && currentX - 1 >= 0) && currentY == 3)
        {
            if(board[currentY][currentX + 1] == lastMovedPawn &&
            targetX == v[1][0].first && targetY == v[1][0].second &&
            board[currentY][currentX + 1] != nullptr)
            {
                flag = true;
                board[currentY][currentX + 1] -> destroy();
                board[currentY][currentX + 1] = nullptr;
            }
            else if(board[currentY][currentX - 1] == lastMovedPawn &&
            targetX == v[2][0].first && targetY == v[2][0].second &&
            board[currentY][currentX - 1] != nullptr)
            {
                flag = true;
                board[currentY][currentX - 1] -> destroy();
                board[currentY][currentX - 1] = nullptr;
            }
        }
    }

    return flag;
}

void GameManager::makeMove(int8_t currentX, int8_t currentY, int8_t targetX, int8_t targetY){
    board[targetY][targetX] = board[currentY][currentX];
    board[currentY][currentX] = nullptr;
    board[targetY][targetX] -> boardX = targetX;
    board[targetY][targetX] -> boardY = targetY;
    board[targetY][targetX] -> isMoved();
}

bool GameManager::checkMate(){
    King *king = nullptr;
    bool gameEnd = false;
    bool breakLoops = false;

    for(int i = 0; i < 8; i++){
        for(int k = 0; k < 8; k++){
            if(board[i][k] == nullptr) continue;
            if(typeid(*board[i][k]) == typeid(King) && board[i][k] -> black == blackMove)
                king = (King*)board[i][k];
        }
    }

    if(king != nullptr){
        if(!canKingMove(king -> boardX, king -> boardY, blackMove,  true)){
        std::cout<<"cds";
            movements v = king -> move(blackMove);

            bool kingCantEscape = true;
            bool pieceCantCover = true;

            if(!v.empty()){
                for(int i = 0; i < 8; i++){

                    if(v[i].empty()) continue;
                    else if(board[v[i][0].second][v[i][0].first] != nullptr) continue;
                    else if(canKingMove(v[i][0].first, v[i][0].second, blackMove, false)){
                        kingCantEscape = false;
                        break;
                    }

                }
            } // v empty

            if(kingCantEscape){
            std::cout<<"cds22";
                try{
                    for(int i = 0; i < 8; i++){
                        for(int k = 0; k < 8; k++){

                            if(board[i][k] == nullptr) continue;
                            else if(board[i][k] -> black == blackMove){

                                v = board[i][k] -> move(blackMove);

                                if(!v.empty()){
                                    for(int g = 0; g < 8; g++){
                                        for(int h = 0; h < 8; h++){
                                            if(!v[g].empty()){

                                                if(typeid(*board[i][k]) == typeid(Pawn) && g != 0) break;
                                                else if(v[g][h].first == king -> checkX && v[g][h].second == king -> checkY &&
                                                        board[i][k] != king){
                                                    breakLoops = true;
                                                    throw breakLoops;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                catch(bool breakLoops){
                    if(breakLoops)
                        pieceCantCover = false;
                }

            } // king cant escape

            if(kingCantEscape && pieceCantCover){
                gameEnd = true;
                std::cout<<"cds3";
            }

        }//if(!canKingMove(king -> boardX, king -> boardY, !blackMove,  true))
    }

    return gameEnd;
}
