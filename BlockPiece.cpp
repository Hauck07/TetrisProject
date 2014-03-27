#include "BlockPiece.h"

BlockPiece::BlockPiece()
{
    std::fill_n(*Block, 4*4, 0);
    srand(time(NULL));
    Color = (rand() % 5) + 1;   // random number between 1 and 6
    Y = (rand() % 5) + 2;       // random number between 2 and 6
    X = 0;
    CurrentPosition = 0;
}

bool BlockPiece::Move(int MoveX, int MoveY, int Board[20][10])
{
    if((MoveY == 1)){
        if(CanMoveRight(Board)){
            Y += MoveY;
            return true;
        }
        else return false;
    }
    else if(MoveY == -1){
        if(CanMoveLeft(Board)){
            Y += MoveY;
            return true;
        }
        else return false;
    }

    if(MoveX == 1 && X < 19){
        if(CanMoveDown(Board)){
            X += MoveX;
            return true;
        }
        else return false;
    }
    else if(MoveX == -1 && X > 0){
        X += MoveX;
        return true;
    }

    return false;
}


bool BlockPiece::CanMoveLeft(int Board[20][10])
{
    for(int h = 0; h < 4; h++){
        for(int w = 0; w < 4; w++){
            if(Block[h][w] == 1){
                if(Board[X+h][Y+w-1] != BLOCK_TYPE_EMPTY || Y+w-1 < 0)
                    return false;
            }
        }
    }
    return true;
}

bool BlockPiece::CanMoveRight(int Board[20][10])
{
    for(int h = 0; h < 4; h++){
        for(int w = 3; w >= 0; w--){
            if(Block[h][w] == 1){
                if(Board[X+h][Y+w+1] != BLOCK_TYPE_EMPTY || Y+w+1 > 9)
                    return false;
            }
        }
    }
    return true;
}

bool BlockPiece::CanMoveDown(int Board[20][10])
{
    for(int h = 0; h < 4; h++){
        for(int w = 0; w < 4; w++){
            if(Block[h][w] == 1 && (X + h + 1 == 20 || Board[X + h + 1][Y + w] != BLOCK_TYPE_EMPTY)){
                return false;
            }
        }
    }
    return true;
}


void BlockPiece::OnRender(SDL_Surface* Destination, SDL_Surface* Source)
{
    for(int Height = 0; Height < 4; Height++){
        for(int Width = 0; Width < 4; Width++){
            if(Block[Height][Width] == 1 && X + Height >= 0)
                SurfaceHandler::OnDraw(Destination, Source, 30+(Y*24)+(24*Width), 40+(X*24)+(24*Height), 0, Color*24, 24, 24);
        }
    }
}

void BlockPiece::OnRenderPreview(SDL_Surface* Destination, SDL_Surface* Source)
{
    int BaseX, BaseY;
    switch(Width){
        case 1:
            BaseX = 68;
            BaseY = 376;
            break;
        case 2:
            BaseX = 86;
            BaseY = 364;
            break;
        case 3:
            BaseX = 94;
            BaseY = 354;
            break;
    }

    for(int h = 0; h < 4; h++){
        for(int w = 0; w < 4; w++){
            if(Block[h][w] == 1)
                SurfaceHandler::OnDraw(Destination, Source, BaseY+(24*w), BaseX+(24*h), 0, Color*24, 24, 24);
        }
    }
}
