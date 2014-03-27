#ifndef BLOCKS_H_INCLUDED
#define BLOCKS_H_INCLUDED
#include "BlockPiece.h"


class BlockS: public BlockPiece{
    public:
        BlockS();

        void Turn(int Block[20][10]);
};

#endif // BLOCKS_H_INCLUDED
