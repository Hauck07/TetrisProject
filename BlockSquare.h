#ifndef BLOCKSQUARE_H_INCLUDED
#define BLOCKSQUARE_H_INCLUDED
#include "BlockPiece.h"

class BlockSquare: public BlockPiece{
    public:
        BlockSquare();

        void Turn(int Block[20][10]);
};


#endif // BLOCKSQUARE_H_INCLUDED
