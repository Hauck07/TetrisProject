#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <SDL/SDL.h>
#include "Define.h"
#include "SurfaceHandler.h"


class Board{
    public:
        int Squares[20][10];

        Board();

        void OnRender(SDL_Surface* Destination, SDL_Surface* Source);

        bool CheckBlock(int Block[4][4], int X, int Y);

        bool CheckBlockDown(int Block[4][4], int X, int Y);

        bool CheckBlockLeft(int Block[4][4], int X, int Y);

        bool CheckBlockRight(int Block[4][4], int X, int Y);

        int* CheckLine();

        void MergeBlock(int Block[4][4], int X, int Y, int Color);

        void BringDownLines(int CurrentX);

        void CleanBoard();

};

#endif // BOARD_H_INCLUDED
