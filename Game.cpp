#include "Game.h"
#include "TextureManager.h"
#include "Pieces.h"
#include "GameManager.h"

SDL_Texture *boardTexture;
SDL_Texture *fieldSelection;
GameManager gameManager;

//Pieces *board[8][8];

bool pieceGrab = false;
int pieceX, pieceY;


Game::Game(){
}

Game::~Game(){
}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen){

    int flag = 0;

    if(fullscreen) flag = SDL_WINDOW_FULLSCREEN;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "SDL Initialised ..." << std::endl;
        window = SDL_CreateWindow(title, xPos, yPos, width, height, flag);

        if(window) std::cout << "Window created" << std::endl;

        renderer = SDL_CreateRenderer(window, -1, 0);

        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }

        runnging = true;
    } else {
        runnging = false;
    }

    boardTexture = TextureManager::LoadTexture("./texture/GreenChessboard.png", renderer);
    fieldSelection = TextureManager::LoadTexture("./texture/field.png", renderer);
    //blackKing = new King(27, 27, "./texture/BlackKing.png", renderer);
    startGame();
}

void Game::handleEvent(){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:
             runnging = false;
             break;

            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){
                    if(!pieceGrab){
                        int moduloX = ((int)event.button.x - 27) / 100;
                        int moduloY = ((int)event.button.y - 27) / 100;

                        if(gameManager.board[moduloY][moduloX] == nullptr) break;

                        pieceGrab = true;
                        pieceX = moduloX;
                        pieceY = moduloY;

                    } else {
                        pieceGrab = false;
                        int moduloX = ((int)event.button.x - 27) / 100;
                        int moduloY = ((int)event.button.y - 27) / 100;
                        //moze umiescic
                        if(gameManager.canMove(pieceX, pieceY, moduloX, moduloY)){
                            gameManager.board[pieceY][pieceX] -> grab((Sint32)((moduloX * 100) + 72), (Sint32)((moduloY * 100) + 72));
                            gameManager.makeMove(pieceX, pieceY, moduloX, moduloY);

                            if(gameManager.checkMate())
                                runnging = false;
                        } else {
                            gameManager.board[pieceY][pieceX] -> grab((Sint32)((pieceX * 100) + 72), (Sint32)((pieceY * 100) + 72));
                        }
                    }
                }

            break;

            default:
                if(pieceGrab){
                    gameManager.board[pieceY][pieceX] -> grab(event.button.x, event.button.y);
                    fieldSelectionMove((event.button.x - 27) / 100, (event.button.y - 27) / 100);
                }
            break;
        }
    }

}

void Game::update(){
}

void Game::render(){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, boardTexture, NULL, NULL);
    if(pieceGrab)
        SDL_RenderCopy(renderer, fieldSelection, &srcRect, &destRect);
    //blackKing -> render();
    for(int i = 0; i < 8; i++){
        for(int k = 0; k < 8; k++){
            if(gameManager.board[i][k] == nullptr) continue;
            gameManager.board[i][k] -> render();
        }
    }
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::cout << "Game cleaned" << std::endl;
}

bool Game::isRunning(){
    return runnging;
}

void Game::startGame(){

int start[8][8] = {-1, -2, -3, -4, -5, -3, -2, -1,
                      -6, -6, -6, -6, -6, -6, -6, -6,
                       0,  0,  0,  0,  0,  0,  0,  0,
                       0,  0,  0,  0,  0,  0,  0,  0,
                       0,  0,  0,  0,  0,  0,  0,  0,
                       0,  0,  0,  0,  0,  0,  0,  0,
                       6,  6,  6,  6,  6,  6,  6,  6,
                       1,  2,  3,  4,  5,  3,  2,  1};

    for(int i = 0; i < 8; i++){
        for(int k = 0; k < 8; k++){
            switch(start[i][k]){
                case 1:
                    gameManager.board[i][k] = new Rook(27 + (k * 100), 27 + (i * 100), "./texture/WhiteRook.png", renderer, false);
                break;

                case 2:
                    gameManager.board[i][k] = new Horse(27 + (k * 100), 27 + (i * 100), "./texture/WhiteHorse.png", renderer, false);
                break;

                case 3:
                    gameManager.board[i][k] = new Bishop(27 + (k * 100), 27 + (i * 100), "./texture/WhiteBishop.png", renderer, false);
                break;

                case 4:
                    gameManager.board[i][k] = new Queen(27 + (k * 100), 27 + (i * 100), "./texture/WhiteHetman.png", renderer, false);
                break;

                case 5:
                    gameManager.board[i][k] = new King(27 + (k * 100), 27 + (i * 100), "./texture/WhiteKing.png", renderer, false);
                break;

                case 6:
                    gameManager.board[i][k] = new Pawn(27 + (k * 100), 27 + (i * 100), "./texture/WhitePawn.png", renderer, false);
                break;

                case -1:
                    gameManager.board[i][k] = new Rook(27 + (k * 100), 27 + (i * 100), "./texture/BlackRook.png", renderer, true);
                break;

                case -2:
                    gameManager.board[i][k] = new Horse(27 + (k * 100), 27 + (i * 100), "./texture/BlackHorse.png", renderer, true);
                break;

                case -3:
                    gameManager.board[i][k] = new Bishop(27 + (k * 100), 27 + (i * 100), "./texture/BlackBishop.png", renderer, true);
                break;

                case -4:
                    gameManager.board[i][k] = new Queen(27 + (k * 100), 27 + (i * 100), "./texture/BlackHetman.png", renderer, true);
                break;

                case -5:
                    gameManager.board[i][k] = new King(27 + (k * 100), 27 + (i * 100), "./texture/BlackKing.png", renderer, true);
                break;

                case -6:
                    gameManager.board[i][k] = new Pawn(27 + (k * 100), 27 + (i * 100), "./texture/BlackPawn.png", renderer, true);
                break;

                default:
                    gameManager.board[i][k] = nullptr;
                break;

            }
        }
    }
}

void Game::fieldSelectionMove(Sint32 x, Sint32 y){
    fieldPositionX = (int)x * 100 + 27;
    fieldPositionY = (int)y * 100 + 27;

    srcRect.w = 100;
    srcRect.h = 100;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = fieldPositionX;
    destRect.y = fieldPositionY;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}
