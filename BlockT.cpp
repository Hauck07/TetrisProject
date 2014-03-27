#include "BlockT.h"

BlockT::BlockT(){
    Block[1][0] = 1;
    Block[1][1] = 1;
    Block[0][1] = 1;
    Block[1][2] = 1;
    Width = 3;
    Height = 2;
}

void BlockT::Turn(int Board[20][10])
{
    switch(CurrentPosition){
        case 0:
            if(X+2 > 19 || Board[X+2][Y+2] != BLOCK_TYPE_EMPTY)
                if(X == 0 || Board[X-1][Y+1] != BLOCK_TYPE_EMPTY)
                    return;
            std::fill_n(*Block, 4*4, 0);
            Block[0][1] = 1;
            Block[1][1] = 1;
            Block[2][1] = 1;
            Block[1][2] = 1;
            CurrentPosition = 1;
            Height = 3;
            Width = 2;
            while(X+2 > 19 || Board[X+2][Y+1] != BLOCK_TYPE_EMPTY)
                X--;
            break;
        case 1:
            if(Y <= 0 || Board[X+1][Y] != BLOCK_TYPE_EMPTY)
                if(Y+3 > 9 || Board[X+1][Y+3] != BLOCK_TYPE_EMPTY)
                    return;
            std::fill_n(*Block, 4*4, 0);
            Block[1][0] = 1;
            Block[1][1] = 1;
            Block[1][2] = 1;
            Block[2][1] = 1;
            CurrentPosition = 2;
            Height = 2;
            Width = 3;
            while(Y < 0 || Board[X+1][Y] != BLOCK_TYPE_EMPTY)
                Y++;
            break;
        case 2:
            if(Board[X][Y+1] != BLOCK_TYPE_EMPTY)
                if(X+3 > 19 || Board[X+3][Y+1] != BLOCK_TYPE_EMPTY)
                    return;
            std::fill_n(*Block, 4*4, 0);
            Block[0][1] = 1;
            Block[1][0] = 1;
            Block[1][1] = 1;
            Block[2][1] = 1;
            CurrentPosition = 3;
            Width = 2;
            Height = 3;
            while(Board[X][Y+1] != BLOCK_TYPE_EMPTY)
                X++;
            break;
        case 3:
            if(Y+2 > 9 || Board[X+1][Y+2] != BLOCK_TYPE_EMPTY)
                if(Y == 0 || Board[X+1][Y-1] != BLOCK_TYPE_EMPTY)
                    return;
            std::fill_n(*Block, 4*4, 0);
            Block[1][0] = 1;
            Block[1][1] = 1;
            Block[0][1] = 1;
            Block[1][2] = 1;
            Width = 3;
            Height = 2;
            CurrentPosition = 0;
            while(Y+2 > 9 || Board[X+1][Y+2] != BLOCK_TYPE_EMPTY)
                Y--;
            break;
    }
}
