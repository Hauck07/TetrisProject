#include "BlockI.h"

BlockI::BlockI()
{
    Block[0][0] = 1;
    Block[1][0] = 1;
    Block[2][0] = 1;
    Block[3][0] = 1;
    Width = 1;
    Height = 4;
}

void BlockI::Turn(int Board[20][10])
{
    if(CurrentPosition == 0){
        if((Y + 3 == 10 || Board[X][Y+3] != BLOCK_TYPE_EMPTY) && Board[X][Y+1] == BLOCK_TYPE_EMPTY && Board[X][Y+2] == BLOCK_TYPE_EMPTY)
            if(Y - 1 < 0 || Board[X][Y-1] != BLOCK_TYPE_EMPTY)
                return;
        if((Y + 2 > 9 || Board[X][Y+2] != BLOCK_TYPE_EMPTY) && Board[X][Y+1] == BLOCK_TYPE_EMPTY)
            if(Y - 1 < 0 || Y - 2 < 0 || Board[X][Y-1] != BLOCK_TYPE_EMPTY || Board[X][Y-2])
                return;
        if(Y + 1 > 9 || Board[X][Y+1] != BLOCK_TYPE_EMPTY)
            if(Y - 1 < 0 || Y - 2 < 0 || Y - 3 < 0 || Board[X][Y-1] != BLOCK_TYPE_EMPTY ||Board[X][Y-2] != BLOCK_TYPE_EMPTY || Board[X][Y-3] != BLOCK_TYPE_EMPTY)
                return;

        std::fill_n(*Block, 4*4, 0);
        Block[0][0] = 1;
        Block[0][1] = 1;
        Block[0][2] = 1;
        Block[0][3] = 1;
        CurrentPosition = 1;
        Width = 4;
        Height = 1;
        while(Y+Width-1 > 9 || Board[X][Y+1] != BLOCK_TYPE_EMPTY || Board[X][Y+2] != BLOCK_TYPE_EMPTY || Board[X][Y+3] != BLOCK_TYPE_EMPTY){
            Y--;
        }
    }
    else if(CurrentPosition == 1){
        if(X+1 > 19 || (Board[X+1][Y] != BLOCK_TYPE_EMPTY))
                return;
        else if(X+2 > 19 || (Board[X+2][Y] != BLOCK_TYPE_EMPTY))
                return;
        else if(X+3 > 19 || (Board[X+3][Y] != BLOCK_TYPE_EMPTY)){
            if(Board[X-1][Y] != BLOCK_TYPE_EMPTY)
                return;
        }
        std::fill_n(*Block, 4*4, 0);
        Block[0][0] = 1;
        Block[1][0] = 1;
        Block[2][0] = 1;
        Block[3][0] = 1;
        CurrentPosition = 0;
        Width = 1;
        Height = 4;
        while(X+Height-1 > 19 || (Board[X+3][Y] != BLOCK_TYPE_EMPTY || Board[X+2][Y] != BLOCK_TYPE_EMPTY || Board[X+1][Y] != BLOCK_TYPE_EMPTY)){
            X--;
        }
    }
}









