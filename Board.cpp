#include "Board.h"
#include <algorithm>

Board::Board(){
    std::fill_n(*Squares, 20*10, 0);
}

void Board::OnRender(SDL_Surface* Destination, SDL_Surface* Source)
{
    for(int X = 0; X < 20; X++){
        for(int Y = 0; Y < 10; Y++){
            SurfaceHandler::OnDraw(Destination, Source, 30+(Y*24), 40+(X*24), 0, Squares[X][Y] * 24, 24, 24);
        }
    }
}

bool Board::CheckBlock(int Block[4][4], int X, int Y)
{
    for(int h = 0; h < 4; h++){
        for(int w = 0; w < 4; w++){
            if(Block[h][w] == 1 && Squares[X+h][Y+w] != BLOCK_TYPE_EMPTY){
                return true;
            }
        }
    }
    return false;
}

bool Board::CheckBlockDown(int Block[4][4], int X, int Y)
{
    for(int h = 0; h < 4; h++){
        for(int w = 0; w < 4; w++){
            if(Block[h][w] == 1 && (X + h + 1 == 20 || Squares[X + h + 1][Y + w] != BLOCK_TYPE_EMPTY)){
                return true;
            }
        }
    }
    return false;
}

bool Board::CheckBlockLeft(int Block[4][4], int X, int Y)
{
    for(int h = 0; h < 4; h++){
        for(int w = 0; w < 4; w++){
            if(Block[h][w] == 1){
                if(Squares[X+h][Y+w-1] != BLOCK_TYPE_EMPTY || Y+w-1 < 0)
                    return true;
            }
        }
    }
    return false;
}

bool Board::CheckBlockRight(int Block[4][4], int X, int Y)
{
    for(int h = 0; h < 4; h++){
        for(int w = 3; w >= 0; w--){
            if(Block[h][w] == 1){
                if(Squares[X+h][Y+w+1] != BLOCK_TYPE_EMPTY || Y+w+1 > 9)
                    return true;
            }
        }
    }
    return false;
}

int* Board::CheckLine()
{
    int* Result = (int*) calloc(4,sizeof(int));

    for(int X = 19; X >= 0; X--){

        bool KeepChecking = false;
        bool LineCompleted = true;
        for(int Y = 0; Y < 10; Y++){
            if(Squares[X][Y] != BLOCK_TYPE_EMPTY)
                KeepChecking = true;
            else
                LineCompleted = false;
        }

        if(LineCompleted == true){
            int ColorBase = Squares[X][0];
            bool ColorMatch = true;

            for(int Y = 1; Y < 10; Y++){
                if(Squares[X][Y] != ColorBase)
                    ColorMatch = false;
                Squares[X][Y] = BLOCK_TYPE_EMPTY;
            }

            BringDownLines(X);
            X++;
            Result[0] += 1;
            if(ColorMatch) Result[3] += 1;
            Result[1] += 10;
            Result[2] += 1;

        }
        else if(KeepChecking == false){
            return Result;
        }
    }
    return Result;
}

void Board::MergeBlock(int Block[4][4], int X, int Y, int Color)
{
     for(int h = 0; h < 4; h++){
        for(int w = 0; w < 4; w++){
            if(Block[h][w] != 0)
                Squares[X + h][Y + w] = Color;
            }
     }
}

void Board::BringDownLines(int CurrentX){
    for(int X = CurrentX; X > 0; X--){
        for(int Y = 0; Y < 10; Y++){
            Squares[X][Y] = Squares[X-1][Y];
        }
    }
}

void Board::CleanBoard(){
    for(int X = 0; X < 20; X++){
        for(int Y = 0; Y < 10; Y++){
            Squares[X][Y] = BLOCK_TYPE_EMPTY;
        }
    }
}
