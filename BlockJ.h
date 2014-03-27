#ifndef BLOCKJ_H_INCLUDED
#define BLOCKJ_H_INCLUDED
#include "BlockPiece.h"

class BlockJ: public BlockPiece{
    public:
        BlockJ();

        void Turn(int Block[20][10]);
};

#endif // BLOCKJ_H_INCLUDED
