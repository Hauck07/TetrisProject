#ifndef BLOCKPIECE_H_INCLUDED
#define BLOCKPIECE_H_INCLUDED

#include "SurfaceHandler.h"
#include "Define.h"

#include <ctime>
#include <algorithm>


enum{
    BLOCK_COLOR_NONE = 0,
    BLOCK_COLOR_RED,
    BLOCK_COLOR_YELLOW,
    BLOCK_COLOR_GREEN,
    BLOCK_COLOR_BLUE,
    BLOCK_COLOR_PURPLE
};


class BlockPiece{

    public:
        int Color;

        int CurrentPosition;

        int X, Y;

        int Block[4][4];

        int Width, Height;

    public:
        BlockPiece();

        bool Move(int MoveX, int MoveY, int Board[20][10]);

        void OnRender(SDL_Surface* Destination, SDL_Surface* Source);

        void OnRenderPreview(SDL_Surface* Destination, SDL_Surface* Source);

        bool CanMoveRight(int Board[20][10]);

        bool CanMoveLeft(int Board[20][10]);

        bool CanMoveDown(int Board[20][10]);

        virtual void Turn(int Board[20][10]) = 0;

};


#endif // BLOCKPIECE_H_INCLUDED
