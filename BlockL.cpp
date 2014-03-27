#include "BlockL.h"

BlockL::BlockL()
{
    Block[0][0] = 1;
    Block[1][0] = 1;
    Block[2][0] = 1;
    Block[2][1]  = 1;
    Width = 2;
    Height = 3;
}

void BlockL::Turn(int Board[20][10])
{
    switch(CurrentPosition){
        case 0:
            if(Board[X][Y+1] != BLOCK_TYPE_EMPTY)
                return;
            if(Y+2 >= 9 || Board[X][Y+2] != BLOCK_TYPE_EMPTY)
                if(Board[X][Y-1] != BLOCK_TYPE_EMPTY || Board[X-1][Y-1] != BLOCK_TYPE_EMPTY || Y == 0)
                    return;
            std::fill_n(*Block, 4*4, 0);
            Block[0][0] = 1;
            Block[1][0] = 1;
            Block[0][1] = 1;
            Block[0][2]  = 1;
            CurrentPosition = 1;
            Width = 3;
            Height = 2;
            while(Y+Width-1 > 9 || Board[X][Y+2] != BLOCK_TYPE_EMPTY)
                Y--;
            break;

        case 1:
            if(Board[X+1][Y+1] != BLOCK_TYPE_EMPTY)
                return;
            if(Board[X+2][Y+1] != BLOCK_TYPE_EMPTY)
                if(Board[X-1][Y] != BLOCK_TYPE_EMPTY || Board[X-1][Y+1] != BLOCK_TYPE_EMPTY)
                    return;
            std::fill_n(*Block, 4*4, 0);
            Block[0][0] = 1;
            Block[0][1] = 1;
            Block[1][1] = 1;
            Block[2][1] = 1;
            CurrentPosition = 2;
            Width = 2;
            Height = 3;
            while(X+Height-1 > 19 || Board[X+2][Y+1] != BLOCK_TYPE_EMPTY)
                X--;
            break;
        case 2:
            if(Board[X+1][Y] != BLOCK_TYPE_EMPTY)
                return;
            if(Y+2 > 9 || Board[X][Y+2] != BLOCK_TYPE_EMPTY || Board[X+1][Y+2] != BLOCK_TYPE_EMPTY)
                if(Board[X-1][Y-1] != BLOCK_TYPE_EMPTY)
                    return;
            std::fill_n(*Block, 4*4, 0);
            Block[1][0] = 1;
            Block[1][1] = 1;
            Block[1][2] = 1;
            Block[0][2] = 1;
            CurrentPosition  = 3;
            Width = 3;
            Height = 2;
            while(Y+2 > 9 || Board[X][Y+2] != BLOCK_TYPE_EMPTY || Board[X+1][Y+2] != BLOCK_TYPE_EMPTY)
                Y--;
            break;
        case 3:
            if(Board[X][Y] != BLOCK_TYPE_EMPTY || Board[X][Y+1] != BLOCK_TYPE_EMPTY)
                return;
            if(X+2 > 19 || Board[X+2][Y] != BLOCK_TYPE_EMPTY || Board[X+2][Y+1] != BLOCK_TYPE_EMPTY)
                if(Board[X-1][Y] != BLOCK_TYPE_EMPTY)
                    return;
            std::fill_n(*Block, 4*4, 0);
            Block[0][0] = 1;
            Block[1][0] = 1;
            Block[2][0] = 1;
            Block[2][1]  = 1;
            CurrentPosition = 0;
            Width = 2;
            Height = 3;
            while(X+2 > 19 || Board[X+2][Y] != BLOCK_TYPE_EMPTY || Board[X+2][Y+1])
                X--;
            break;

    }
}
