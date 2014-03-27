#ifndef BLOCKZ_H_INCLUDED
#define BLOCKZ_H_INCLUDED
#include "BlockPiece.h"

class BlockZ: public BlockPiece{
    public:
        BlockZ();

        void Turn(int Block[20][10]);
};

#endif // BLOCKZ_H_INCLUDED
