#include "GameManager.h"

Pieces* lastMovedPawn;
King* king;
Rook* rook;

GameManager::GameManager(){
    blackMove = false;
}

bool GameManager::canMove(int8_t currentX, int8_t currentY, int8_t targetX, int8_t targetY){

    if((board[currentY][currentX] -> black && blackMove) || (!board[currentY][currentX] -> black && ! blackMove)){

        std::array<std::vector<std::pair<int, int>>, 8> v;

        bool flag = true;

        v = board[currentY][currentX] -> move(blackMove);

        if(!v.empty()){

            if(typeid(*board[currentY][currentX]) == typeid(King)){
                king = (King*)board[currentY][currentX];

                /* Roszada */
                if((targetX == 6 || targetX == 2) && !king -> makedMove()){
                    int8_t rookX = targetX == 6 ? 7 : 0;

                    if(typeid(*board[currentY][rookX]) == typeid(Rook)){
                        rook = (Rook*)board[currentY][rookX];

                            if(!rook -> makedMove()){
                                if(rookX == 0){
                                    for(int g = currentX - 2; g > rookX; g--){
                                        if(board[currentY][g] != nullptr) flag = false;
                                    }
                                } else {
                                    for(int g = currentX + 1; g < rookX; g++){
                                        if(board[currentY][g] != nullptr) flag = false;
                                    }
                                }
                                if(flag){
                                    if(targetX == 6){
                                        board[currentY][rookX] -> grab((Sint32)((5 * 100) + 72), (Sint32)((currentY * 100) + 72));
                                        board[currentY][rookX] -> boardX = 5;
                                        board[currentY][5] = board[currentY][rookX];
                                    } else {
                                        board[currentY][rookX] -> grab((Sint32)((3 * 100) + 72), (Sint32)((currentY * 100) + 72));
                                        board[currentY][rookX] -> boardX = 3;
                                        board[currentY][3] = board[currentY][rookX];
                                    }

                                    board[currentY][rookX] -> boardY = currentY;
                                    board[currentY][rookX] -> isMoved();
                                    board[currentY][currentX] -> isMoved();
                                    board[currentY][rookX] = nullptr;

                                    board[currentY][currentX] -> boardX = targetX;
                                    board[currentY][currentX] -> grab((Sint32)((targetX * 100) + 72), (Sint32)((targetY * 100) + 72));
                                    board[targetY][targetX] = board[currentY][currentX];
                                    board[currentY][currentX] = nullptr;

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
                        for(int g = 1; g < k; g++){
                            if(board[v[i][g].second][v[i][g].first] != nullptr)
                                flag = false;
                        }

                        if(board[targetY][targetX] != nullptr && flag){
                            if(!((board[targetY][targetX] -> black && !blackMove) ||
                                (!board[targetY][targetX] -> black && blackMove)))
                                    flag = false;
                        }

                        if(typeid(*board[currentY][currentX]) == typeid(Pawn) && flag){

                            /* Bicie w przelocie */

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
                                    if((board[v[1][0].second][v[1][0].first] == nullptr ? true : board[v[1][0].second][v[1][0].first] -> black)&&
                                       (board[v[2][0].second][v[2][0].first] == nullptr ? true : board[v[2][0].second][v[2][0].first] -> black))
                                            flag = false;

                                    if((currentX + 1 < 8 && currentX - 1 >= 0) && currentY == 4){
                                        if(board[currentY][currentX + 1] == lastMovedPawn &&
                                            targetX == v[1][0].first && targetY == v[1][0].second &&
                                            board[currentY][currentX + 1] != nullptr){
                                                flag = true;
                                                board[currentY][currentX + 1] -> destroy();
                                                board[currentY][currentX + 1] = nullptr;
                                        } else if(board[currentY][currentX - 1] == lastMovedPawn &&
                                            targetX == v[2][0].first && targetY == v[2][0].second &&
                                            board[currentY][currentX - 1] != nullptr){
                                                flag = true;
                                                board[currentY][currentX - 1] -> destroy();
                                                board[currentY][currentX - 1] = nullptr;
                                        }
                                    }
                                } else {
                                    if((board[v[1][0].second][v[1][0].first] == nullptr ? true : !board[v[1][0].second][v[1][0].first] -> black)&&
                                       (board[v[2][0].second][v[2][0].first] == nullptr ? true : !board[v[2][0].second][v[2][0].first] -> black))
                                            flag = false;

                                    if((currentX + 1 < 8 && currentX - 1 >= 0) && currentY == 3){
                                        if(board[currentY][currentX + 1] == lastMovedPawn &&
                                            targetX == v[1][0].first && targetY == v[1][0].second &&
                                            board[currentY][currentX + 1] != nullptr){
                                                flag = true;
                                                board[currentY][currentX + 1] -> destroy();
                                                board[currentY][currentX + 1] = nullptr;
                                        } else if(board[currentY][currentX - 1] == lastMovedPawn &&
                                            targetX == v[2][0].first && targetY == v[2][0].second &&
                                            board[currentY][currentX - 1] != nullptr){
                                                flag = true;
                                                board[currentY][currentX - 1] -> destroy();
                                                board[currentY][currentX - 1] = nullptr;
                                        }
                                    }
                                }
                            }
                        }

                        if(flag){
                            if(typeid(*board[currentY][currentX]) == typeid(Pawn))
                                lastMovedPawn = (Pawn*)board[currentY][currentX];
                            else
                                lastMovedPawn = nullptr;

                            if(board[targetY][targetX] != nullptr)
                                board[targetY][targetX] -> destroy();

                            board[currentY][currentX] -> grab((Sint32)((targetX * 100) + 72), (Sint32)((targetY * 100) + 72));
                            board[currentY][currentX] -> boardX = targetX;
                            board[currentY][currentX] -> boardY = targetY;
                            board[currentY][currentX] -> isMoved();
                            board[targetY][targetX] = board[currentY][currentX];
                            board[currentY][currentX] = nullptr;

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
