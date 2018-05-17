#include "GameManager.h"

Pieces* lastMovedPawn;


GameManager::GameManager(){
    blackMove = false;
}

bool GameManager::canMove(int currentX, int currentY, int targetX, int targetY){

    bool flag = false;

    if(board[currentY][currentX] -> black == blackMove){

        if(!move(board[currentY][currentX], targetX, targetY)){
            if(typeid(*board[currentY][currentX]) == typeid(King)){
                King* king = (King*)board[currentY][currentX];

                if((targetX == 6 || targetX == 2) && !king -> makedMove()){
                    int rookX = targetX == 6 ? 7 : 0;

                    if(typeid(*board[currentY][rookX]) == typeid(Rook)){
                        Rook* rook = (Rook*)board[currentY][rookX];

                            if(!rook -> makedMove()){
                                if(castle(rookX, currentX, currentY)){
                                    flag = true;
                                }
                            }
                        }
                }
            }

            else if(typeid(*board[currentY][currentX]) == typeid(Pawn)){
                if(enPassant(currentX, currentY, targetX, targetY)){
                    flag = true;
                }
            }
        } else {
            flag = true;
        }

        if(flag){
            if(typeid(*board[currentY][currentX]) == typeid(Pawn) && !((Pawn*)board[currentY][currentX]) -> makedMove())
                    lastMovedPawn = (Pawn*)board[currentY][currentX];
            else
                lastMovedPawn = nullptr;

            blackMove ^= true;
        }
    }

    return flag;
}

bool GameManager::canKingMove(int targetX, int targetY, bool blackTurn, bool check){
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

                                    for(int r = 0; r < p; r++){
                                        if(board[v[g][r].second][v[g][r].first] != nullptr &&
                                            typeid(*board[v[g][r].second][v[g][r].first]) != typeid(King)){
                                            flag = false;

                                            break;
                                        }
                                    }

                                    if(flag){

                                        if(check){
                                            King *king = (King*)board[targetY][targetX];

                                            king -> whoCheckX = board[i][k] -> boardX;
                                            king -> whoCheckY = board[i][k] -> boardY;

                                            if(p != 0){
                                                king -> checkX = v[g][p-1].first;
                                                king -> checkY = v[g][p-1].second;
                                            } else {
                                                king -> checkX = -1;
                                                king -> checkY = -1;
                                            }

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

bool GameManager::castle(int rookX, int currentX, int currentY){

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

bool GameManager::enPassant(int currentX, int currentY, int targetX, int targetY){

    /* Bicie w przelocie */

    bool flag = false;
    movements v = board[currentY][currentX] -> move(blackMove);

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

void GameManager::makeMove(int currentX, int currentY, int targetX, int targetY){

    if(board[targetY][targetX] != nullptr)
        board[targetY][targetX] -> destroy();

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
            movements v = king -> move(blackMove);

            bool kingCantEscape = true;
            bool pieceCantCover = true;

            if(!v.empty()){
                for(int i = 0; i < 8; i++){

                    if(v[i].empty()) continue;

                    else if(board[v[i][0].second][v[i][0].first] != nullptr &&
                            board[v[i][0].second][v[i][0].first] -> black == blackMove) continue;

                    else if(canKingMove(v[i][0].first, v[i][0].second, blackMove, false)){
                        kingCantEscape = false;
                        break;
                    }

                }
            } // v empty

            if(kingCantEscape){
                try{
                    for(int i = 0; i < 8; i++){
                        for(int k = 0; k < 8; k++){

                            if(board[i][k] == nullptr) continue;
                            else if(board[i][k] -> black == blackMove && board[i][k] != king){

                                if(move(board[i][k], king -> whoCheckX, king -> whoCheckY)){
                                    breakLoops = true;
                                    throw breakLoops;
                                }

                                else if(king -> checkX != -1 && king -> checkY != -1){
                                    if(move(board[i][k], king -> checkX, king -> checkY)){
                                        breakLoops = true;
                                        throw breakLoops;
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

            if(kingCantEscape && pieceCantCover)
                gameEnd = true;

            king -> checkX = -1;
            king -> checkY = -1;
            king -> whoCheckX = -1;
            king -> whoCheckY = -1;
        }//if(!canKingMove(king -> boardX, king -> boardY, !blackMove,  true))
    }

    return gameEnd;
}

bool GameManager::move(Pieces *wsk, int x, int y){
    bool flag = false;
    bool breakLoops = false;
    movements v;


    if(board[y][x] == nullptr || (board[y][x] != nullptr && board[y][x] -> black != blackMove)){
        v = wsk -> move(blackMove);

        if(!v.empty()){

            try{
                for(int i = 0; i < 8; i++){

                    if(v[i].empty()) continue;

                    for(int k = 0; k < v[i].size(); k++){
                        if(v[i][k].first == x && v[i][k].second == y){

                            //* Sprawdzanie ruchów piona *//

                            if(typeid(*wsk) == typeid(Pawn)){

                                if(i == 0){
                                    if(k == 0){
                                        if(blackMove && y + 1 < 8){
                                            if(board[y][x] == nullptr){
                                                breakLoops = true;
                                                throw breakLoops;
                                            }
                                        }

                                        else if(!blackMove && y - 1 >= 0){
                                            if(board[y][x] == nullptr){
                                                breakLoops = true;
                                                throw breakLoops;
                                            }
                                        }
                                    }

                                    else{
                                        if(blackMove){
                                            if(board[y][x] == nullptr && board[y-1][x] == nullptr){
                                                breakLoops = true;
                                                throw breakLoops;
                                            }
                                        }

                                        else{
                                            if(board[y][x] == nullptr && board[y+1][x] == nullptr){
                                                breakLoops = true;
                                                throw breakLoops;
                                            }
                                        }
                                    }
                                }

                                else{
                                    if(blackMove){
                                        if(!(board[v[i][0].second][v[i][0].first] == nullptr ? true : board[v[i][0].second][v[i][0].first] -> black)){
                                            breakLoops = true;
                                            throw breakLoops;
                                        }
                                    }

                                    else{
                                        if(!(board[v[i][0].second][v[i][0].first] == nullptr ? true : !board[v[i][0].second][v[i][0].first] -> black)){
                                            breakLoops = true;
                                            throw breakLoops;
                                        }
                                    }
                                }
                            }//* pion *//

                            //* Sprawdzanie krola *//

                            else if(typeid(*wsk) == typeid(King)){
                                if(canKingMove(x, y, blackMove,  false)){
                                    breakLoops = true;
                                    throw breakLoops;
                                }
                            }//Krol

                            else{

                                bool check = true;

                                for(int g = 0; g < k; g++){
                                    if(board[v[i][g].second][v[i][g].first] != nullptr)
                                        check = false;
                                }

                                if(check){
                                    breakLoops = true;
                                    throw breakLoops;
                                }
                            }
                        }//  if(v[i][k].first == x && v[i][k].second == y)
                    }
                }
            }

            catch(bool breakLoops){
                if(breakLoops)
                    flag = true;
            }
        }
    }

    return flag;
}
