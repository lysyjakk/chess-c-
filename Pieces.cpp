#include "Pieces.h"
#include "TextureManager.h"

Pieces::Pieces(int xPos, int yPos, const char* texture, SDL_Renderer *renderer, bool black){
    this -> renderer = renderer;
    this -> xPos = xPos;
    this -> yPos = yPos;

    this -> black = black;

    this -> boardX = ((xPos - 27) / 100);
    this -> boardY = ((yPos - 27) / 100);

    this -> srcRect.w = 99;
    this -> srcRect.h = 99;
    this -> srcRect.x = 0;
    this -> srcRect.y = 0;

    this -> destRect.x = xPos;
    this -> destRect.y = yPos;
    this -> destRect.w = this -> srcRect.w;
    this -> destRect.h = this -> srcRect.h;

    objTexture = TextureManager::LoadTexture(texture, renderer);
}

void Pieces::grab(Sint32 x, Sint32 y){
    this -> xPos = (int)x;
    this -> yPos = (int)y;

    this -> srcRect.w = 99;
    this -> srcRect.h = 99;
    this -> srcRect.x = 0;
    this -> srcRect.y = 0;

    this -> destRect.x = xPos - 45;
    this -> destRect.y = yPos - 45;
    this -> destRect.w = this -> srcRect.w;
    this -> destRect.h = this -> srcRect.h;
}



/*<< KING >>*/



King::King(int xPos, int yPos, const char* texture, SDL_Renderer *renderer, bool black):Pieces(xPos, yPos, texture, renderer, black){
    this -> makedMoved = false;
    this -> weight = -1;
}

King::~King(){
}

void King::update(){
    this -> xPos += 1;

    this -> srcRect.w = 99;
    this -> srcRect.h = 99;
    this -> srcRect.x = 0;
    this -> srcRect.y = 0;

    this -> destRect.x = xPos;
    this -> destRect.y = yPos;
    this -> destRect.w = this -> srcRect.w;
    this -> destRect.h = this -> srcRect.h;
}

void King::render(){
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

std::array<std::vector<std::pair<int, int>>, 8> King::move(bool black){
    std::array<std::vector<std::pair<int, int>>, 8> v;

    if(boardX + 1 < 8 && boardY + 1 < 8) v[0].push_back(std::make_pair(boardX  + 1, boardY + 1));
    if(boardX - 1 >= 0 && boardY + 1 < 8) v[1].push_back(std::make_pair(boardX  - 1, boardY + 1));
    if(boardX - 1 >= 0 && boardY - 1 >= 0) v[2].push_back(std::make_pair(boardX  - 1, boardY - 1));
    if(boardX + 1 < 8 && boardY - 1 >= 0) v[3].push_back(std::make_pair(boardX  + 1, boardY - 1));
    if(boardY + 1 < 8) v[4].push_back(std::make_pair(boardX, boardY + 1));
    if(boardY - 1 >= 0) v[5].push_back(std::make_pair(boardX, boardY - 1));
    if(boardX + 1 < 8) v[6].push_back(std::make_pair(boardX + 1, boardY));
    if(boardX - 1 >= 0) v[7].push_back(std::make_pair(boardX - 1, boardY));

    return v;
}

void King::destroy(){
    delete this;
}

void King::isMoved(){
    this -> makedMoved = true;
}

bool King::makedMove(){
    return makedMoved;
}


/*<< QUEEN >>*/



Queen::Queen(int xPos, int yPos, const char* texture, SDL_Renderer *renderer, bool black):Pieces(xPos, yPos, texture, renderer, black){
    this -> weight = 9;
}

Queen::~Queen(){
}

void Queen::update(){
}

void Queen::render(){
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

std::array<std::vector<std::pair<int, int>>, 8> Queen::move(bool black){
    std::array<std::vector<std::pair<int, int>>, 8> v;

    for(int i = 0; i < 8; i++){
        if(boardX + i < 8 && boardY + i < 8) v[0].push_back(std::make_pair(boardX  + i, boardY + i));
        if(boardX - i >= 0 && boardY + i < 8) v[1].push_back(std::make_pair(boardX  - i, boardY + i));
        if(boardX - i >= 0 && boardY - i >= 0) v[2].push_back(std::make_pair(boardX  - i, boardY - i));
        if(boardX + i < 8 && boardY - i >= 0) v[3].push_back(std::make_pair(boardX  + i, boardY - i));
        if(boardY + i < 8) v[4].push_back(std::make_pair(boardX, boardY + i));
        if(boardY - i >= 0) v[5].push_back(std::make_pair(boardX, boardY - i));
        if(boardX + i < 8) v[6].push_back(std::make_pair(boardX + i, boardY));
        if(boardX - i >= 0) v[7].push_back(std::make_pair(boardX - i, boardY));
    }

    return v;
}

void Queen::destroy(){
    delete this;
}

void Queen::isMoved(){
    return;
}


/*<< BISHOP >>*/



Bishop::Bishop(int xPos, int yPos, const char* texture, SDL_Renderer *renderer, bool black):Pieces(xPos, yPos, texture, renderer, black){
    this -> weight = 3;
}

Bishop::~Bishop(){
}

void Bishop::update(){
}

void Bishop::render(){
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

std::array<std::vector<std::pair<int, int>>, 8> Bishop::move(bool black){
    std::array<std::vector<std::pair<int, int>>, 8> v;

    for(int i = 0; i < 8; i++){
        if(boardX + i < 8 && boardY + i < 8) v[0].push_back(std::make_pair(boardX  + i, boardY + i));
        if(boardX - i >= 0 && boardY + i < 8) v[1].push_back(std::make_pair(boardX  - i, boardY + i));
        if(boardX - i >= 0 && boardY - i >= 0) v[2].push_back(std::make_pair(boardX  - i, boardY - i));
        if(boardX + i < 8 && boardY - i >= 0) v[3].push_back(std::make_pair(boardX  + i, boardY - i));
    }

    return v;
}

void Bishop::destroy(){
    delete this;
}

void Bishop::isMoved(){
    return;
}


/*<< HORSE >>*/



Horse::Horse(int xPos, int yPos, const char* texture, SDL_Renderer *renderer, bool black):Pieces(xPos, yPos, texture, renderer, black){
    this -> weight = 3;
}

Horse::~Horse(){
}

void Horse::update(){
}

void Horse::render(){
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

std::array<std::vector<std::pair<int, int>>, 8> Horse::move(bool black){
    std::array<std::vector<std::pair<int, int>>, 8> v;

    if(boardX + 2 < 8 && boardY + 1 < 8) v[0].push_back(std::make_pair(boardX  + 2, boardY + 1));
    if(boardX + 2 < 8 && boardY - 1 >= 0) v[1].push_back(std::make_pair(boardX + 2, boardY - 1));
    if(boardX - 2 >= 0 && boardY + 1 < 8) v[2].push_back(std::make_pair(boardX - 2, boardY + 1));
    if(boardX - 2 >= 0 && boardY - 1 >= 0) v[3].push_back(std::make_pair(boardX - 2, boardY - 1));
    if(boardX + 1 < 8 && boardY + 2 < 8) v[4].push_back(std::make_pair(boardX + 1, boardY + 2));
    if(boardX - 1 >= 0 && boardY + 2 < 8) v[5].push_back(std::make_pair(boardX - 1, boardY + 2));
    if(boardX + 1 < 8 && boardY - 2 >= 0) v[6].push_back(std::make_pair(boardX + 1, boardY - 2));
    if(boardX - 1 >= 0 && boardY -2 >= 0) v[7].push_back(std::make_pair(boardX - 1, boardY - 2));


    return v;
}

void Horse::destroy(){
    delete this;
}

void Horse::isMoved(){
    return;
}


/*<< ROOK >>*/



Rook::Rook(int xPos, int yPos, const char* texture, SDL_Renderer *renderer, bool black):Pieces(xPos, yPos, texture, renderer, black){
    this -> weight = 5;
    this -> makedMoved = false;
}

Rook::~Rook(){
}

void Rook::update(){
}

void Rook::render(){
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

std::array<std::vector<std::pair<int, int>>, 8> Rook::move(bool blackMove){
    std::array<std::vector<std::pair<int, int>>, 8> v;

    for(int i = 0; i < 8; i ++){
        if(boardY + i < 8) v[0].push_back(std::make_pair(boardX, boardY + i));
        if(boardY - i >= 0) v[1].push_back(std::make_pair(boardX, boardY - i));
        if(boardX + i < 8) v[2].push_back(std::make_pair(boardX + i, boardY));
        if(boardX - i >= 0) v[3].push_back(std::make_pair(boardX - i, boardY));
    }

    return v;
}

void Rook::destroy(){
    delete this;
}

void Rook::isMoved(){
    this -> makedMoved = true;
}

bool Rook::makedMove(){
    return makedMoved;
}

/*<< PAWN >>*/



Pawn::Pawn(int xPos, int yPos, const char* texture, SDL_Renderer *renderer, bool black):Pieces(xPos, yPos, texture, renderer, black){
    this -> weight = 1;
    this -> makedMoved = false;
}
Pawn::~Pawn(){
}

void Pawn::update(){
}

void Pawn::render(){
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

std::array<std::vector<std::pair<int, int>>, 8> Pawn::move(bool blackMove){
    std::array<std::vector<std::pair<int, int>>, 8> v;

    if(!makedMoved){
        if(blackMove){
            v[0].push_back(std::make_pair(boardX, boardY + 1));
            v[0].push_back(std::make_pair(boardX, boardY + 2));

            if(boardX + 1 < 8 && boardY + 1 < 8) v[1].push_back(std::make_pair(boardX + 1, boardY + 1));
            else v[1].push_back(std::make_pair(boardX, boardY));
            if(boardX - 1 >= 0 && boardY + 1 < 8) v[2].push_back(std::make_pair(boardX - 1, boardY + 1));
            else v[2].push_back(std::make_pair(boardX, boardY));
        } else {
            v[0].push_back(std::make_pair(boardX, boardY - 1));
            v[0].push_back(std::make_pair(boardX, boardY - 2));

            if(boardX + 1 < 8 && boardY - 1 >= 0) v[1].push_back(std::make_pair(boardX + 1, boardY - 1));
            else v[1].push_back(std::make_pair(boardX, boardY));
            if(boardX - 1 >= 0 && boardY - 1 >= 0) v[2].push_back(std::make_pair(boardX - 1, boardY - 1));
            else v[2].push_back(std::make_pair(boardX, boardY));
        }
    } else {
        if((boardY + 1) < 8 && blackMove){
            v[0].push_back(std::make_pair(boardX, boardY + 1));

            if(boardX + 1 < 8 && boardY + 1 < 8) v[1].push_back(std::make_pair(boardX + 1, boardY + 1));
            else v[1].push_back(std::make_pair(boardX, boardY));
            if(boardX - 1 >= 0 && boardY + 1 < 8) v[2].push_back(std::make_pair(boardX - 1, boardY + 1));
            else v[2].push_back(std::make_pair(boardX, boardY));
        }
        else if((boardY - 1) >= 0 && !blackMove){
            v[0].push_back(std::make_pair(boardX, boardY - 1));

            if(boardX + 1 < 8 && boardY - 1 >= 0) v[1].push_back(std::make_pair(boardX + 1, boardY - 1));
            else v[1].push_back(std::make_pair(boardX, boardY));
            if(boardX - 1 >= 0 && boardY - 1 >= 0) v[2].push_back(std::make_pair(boardX - 1, boardY - 1));
            else v[2].push_back(std::make_pair(boardX, boardY));
        }
    }

    return v;
}

void Pawn::destroy(){
    delete this;
}

void Pawn::isMoved(){
    this -> makedMoved = true;
}
