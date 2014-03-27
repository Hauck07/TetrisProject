#include "BlockS.h"

BlockS::BlockS()
{
    Block[1][0] = 1;
    Block[1][1] = 1;
    Block[0][1] = 1;
    Block[0][2] = 1;
    Width = 3;
    Height = 2;
}

void BlockS::Turn(int Board[20][10])
{
    if(CurrentPosition == 0){
        if(Board[X][Y] != BLOCK_TYPE_EMPTY)
            return;
        if(X+2 > 19 || Board[X+2][Y+1] != BLOCK_TYPE_EMPTY)
            if(Board[X-1][Y] != BLOCK_TYPE_EMPTY || X == 0)
                return;
        std::fill_n(*Block, 4*4, 0);
        Block[0][0] = 1;
        Block[1][0] = 1;
        Block[1][1] = 1;
        Block[2][1] = 1;
        Height = 3;
        Width = 2;
        CurrentPosition = 1;
        while(X+2 > 19 || Board[X+2][Y+1] != BLOCK_TYPE_EMPTY)
            X--;
    }
    else if(CurrentPosition == 1)
    {
        if(Board[X][Y+1] != BLOCK_TYPE_EMPTY)
            return;
        if(Y+2 > 9 || Board[X][Y+2] != BLOCK_TYPE_EMPTY)
            if(Y == 0 || Board[X+1][Y-1] != BLOCK_TYPE_EMPTY)
                return;
        std::fill_n(*Block, 4*4, 0);
        Block[1][0] = 1;
        Block[1][1] = 1;
        Block[0][1] = 1;
        Block[0][2] = 1;
        Width = 3;
        Height = 2;
        CurrentPosition = 0;
        while(Y+2 > 9 || Board[X][Y+2] != BLOCK_TYPE_EMPTY)
            Y--;
    }
}
